import cv2
import numpy as np
from math import sqrt
from time import time


def apply_cfa(image_path, output_dir, cfa_type='bayer'):
    image = cv2.imread(image_path)
    if image is None:
        raise ValueError("Image not found or unable to load.")

    cfa_image = np.zeros_like(image)

    match cfa_type:
        case 'bayer':
            # Bayer pattern:
            # G R
            # B G

            cfa_image[0::2, 1::2, 0] = image[0::2, 1::2, 0]  # R
            cfa_image[0::2, 0::2, 1] = image[0::2, 0::2, 1]  # G (top left)
            cfa_image[1::2, 1::2, 1] = image[1::2, 1::2, 1]  # G (bottom right)
            cfa_image[1::2, 0::2, 2] = image[1::2, 0::2, 2]  # B

        case 'xtrans':
            # Fuji X-Trans pattern:
            # G B R G R B
            # R G G B G G
            # B G G R G G
            # G R B G B R
            # B G G R G G
            # R G G B G G

            # Red
            cfa_image[0::6, 2::6, 0] = image[0::6, 2::6, 0]  # (0, 2)
            cfa_image[0::6, 4::6, 0] = image[0::6, 4::6, 0]  # (0, 4)
            cfa_image[1::6, 0::6, 0] = image[1::6, 0::6, 0]  # (1, 0)
            cfa_image[5::6, 0::6, 0] = image[5::6, 0::6, 0]  # (5, 0)
            cfa_image[2::6, 3::6, 0] = image[2::6, 3::6, 0]  # (2, 3)
            cfa_image[3::6, 1::6, 0] = image[3::6, 1::6, 0]  # (3, 1)
            cfa_image[3::6, 5::6, 0] = image[3::6, 5::6, 0]  # (3, 5)
            cfa_image[4::6, 3::6, 0] = image[4::6, 3::6, 0]  # (4, 3)

            # Green
            cfa_image[0::3, 0::3, 1] = image[0::3, 0::3, 1]  # (0, 0), (0, 3), (3, 0), (3, 3)
            cfa_image[1::3, 1::3, 1] = image[1::3, 1::3, 1]  # (1, 1), (1, 4), (4, 1), (4, 4)
            cfa_image[1::3, 2::3, 1] = image[1::3, 2::3, 1]  # (1, 2), (1, 5), (4, 2), (4, 5)
            cfa_image[2::3, 1::3, 1] = image[2::3, 1::3, 1]  # (2, 1), (2, 4), (5, 1), (5, 4)
            cfa_image[2::3, 2::3, 1] = image[2::3, 2::3, 1]  # (2, 2), (2, 5), (5, 2), (5, 5)

            # Blue
            cfa_image[0::6, 1::6, 2] = image[0::6, 1::6, 2]  # (0, 1)
            cfa_image[0::6, 5::6, 2] = image[0::6, 5::6, 2]  # (0, 5)
            cfa_image[1::6, 3::6, 2] = image[1::6, 3::6, 2]  # (1, 3)
            cfa_image[2::6, 0::6, 2] = image[2::6, 0::6, 2]  # (2, 0)
            cfa_image[3::6, 2::6, 2] = image[3::6, 2::6, 2]  # (3, 2)
            cfa_image[3::6, 4::6, 2] = image[3::6, 4::6, 2]  # (3, 4)
            cfa_image[4::6, 0::6, 2] = image[4::6, 0::6, 2]  # (4, 0)
            cfa_image[5::6, 3::6, 2] = image[5::6, 3::6, 2]  # (5, 3)

        case _:
            raise ValueError("Invalid keyword 'cfa_type' value. Possible values: 'bayer', 'xtrans'")

    output_path = f"{output_dir}{cfa_type}_image.png"
    cv2.imwrite(output_path, cfa_image)
    return output_path


def nearest_neighbour(pixels, mask, coordinates, channel):
    """
    :param pixels: CFA values
    :param mask: CFA mask
    :param coordinates: coordinates of the target pixel
    :param channel: index of the channel to interpolate
    :return: interpolated value of the single channel
    """
    max_y, max_x = pixels.shape[:2]

    # left, top, right, bottom
    for dy, dx in [(0, -1), (-1, 0), (0, 1), (1, 0)]:
        y = coordinates[0] + dy
        x = coordinates[1] + dx
        if y < max_y and x < max_x and mask[y, x, channel]:
            return pixels[y, x, channel]
    return 0


def linear(pixels, mask, coordinates, channel):
    """
    :param pixels: CFA values
    :param mask: CFA mask
    :param coordinates: coordinates of the target pixel
    :param channel: index of the channel to interpolate
    :return: interpolated value of the single channel
    """
    max_y, max_x = pixels.shape[:2]
    valid_neighbours = []

    # left, top, right, bottom
    for dy, dx in [(0, -1), (-1, 0), (0, 1), (1, 0)]:
        y = min(coordinates[0] + dy, max_y - 1)
        x = min(coordinates[1] + dx, max_x - 1)
        if mask[y, x, channel]:
            valid_neighbours.append(int(pixels[y, x, channel]))
    if valid_neighbours:
        return np.uint8(round(sum(valid_neighbours) / len(valid_neighbours)))

    # if there are no neighbours of given channel and that channel is not green (so red/blue channel and no red/blue neighbours)
    elif channel != 1:
        for dy, dx in [(0, -1), (-1, 0), (0, 1), (1, 0)]:
            y = min(coordinates[0] + dy, max_y - 1)
            x = min(coordinates[1] + dx, max_x - 1)
            if mask[y, x, 1]:
                valid_neighbours.append(int(pixels[y, x, 1]))
        if valid_neighbours:
            return np.uint8(round(sum(valid_neighbours) / len(valid_neighbours)))

    # if we are interpolating the green channel, and there are no green neighbours -> mean from red and blue pixels
    else:
        for dy, dx in [(0, -1), (-1, 0), (0, 1), (1, 0)]:
            y = min(coordinates[0] + dy, max_y - 1)
            x = min(coordinates[1] + dx, max_x - 1)
            # if it is red pixel
            if mask[y, x, 0]:
                valid_neighbours.append(pixels[y, x, 0])
            # we know that it is blue pixel (since it's not green nor red)
            else:
                valid_neighbours.append(int(pixels[y, x, 2]))
        if valid_neighbours:
            return np.uint8(round(sum(valid_neighbours) / len(valid_neighbours)))

    return 0


def cubic(pixels, mask, coordinates, channel):
    """
    :param pixels: CFA values
    :param mask: CFA mask
    :param coordinates: coordinates of the target pixel
    :param channel: index of the channel to interpolate
    :return: interpolated value of the single channel

    Using Cubic B-Spline interpolation. Weights calculated by the formula:\n
    |x| <= 1: W(x) = 1/2 * |x|^3 - |x|^2 + 2/3\n
    1 < |x| < 2: W(x) = -1/6 * |x|^3 + |x|^2 -2 * |x| + 4/3\n

    |x| = sqrt(dy^2 + dx^2)
    """
    max_y, max_x = pixels.shape[:2]
    weights = []
    values = []
    result = 0

    for dy, dx in [(0, -1), (-1, 0), (1, 0), (0, 1)]:
        y = min(coordinates[0] + dy, max_y - 1)
        x = min(coordinates[1] + dx, max_x - 1)
        if mask[y, x, channel]:
            distance = sqrt(dy**2 + dx**2)
            weights.append((1/2 * (distance ** 3) - (distance ** 2) + 2/3))
            values.append(int(pixels[y, x, channel]))

    for dy, dx in [(-1, -1), (1, -1), (-1, 1), (1, 1)]:
        y = min(coordinates[0] + dy, max_y - 1)
        x = min(coordinates[1] + dx, max_x - 1)
        if mask[y, x, channel]:
            distance = sqrt(dy**2 + dx**2)
            weights.append((-1/6 * (distance ** 3) + (distance ** 2) - 2 * distance + 4/3))
            values.append(int(pixels[y, x, channel]))

    if weights:
        total = sum(weights)
        weights = [weight/total for weight in weights]
        result = sum([v * w for v, w in zip(values, weights)])

    return np.uint8(result)


def demosaicing_cfa(image_path, output_dir, cfa_type='bayer', interpolation_method='nearest'):
    image = cv2.imread(image_path)
    if image is None:
        raise ValueError("Image not found or unable to load.")

    pixel_mask = np.zeros_like(image, dtype=bool)

    match cfa_type:
        case 'bayer':
            # R
            pixel_mask[0::2, 1::2, 0] = True

            # G
            pixel_mask[0::2, 0::2, 1] = True
            pixel_mask[1::2, 1::2, 1] = True

            # B
            pixel_mask[1::2, 0::2, 2] = True
        case 'xtrans':
            # R
            pixel_mask[0::6, 2::6, 0] = True
            pixel_mask[0::6, 4::6, 0] = True
            pixel_mask[1::6, 0::6, 0] = True
            pixel_mask[5::6, 0::6, 0] = True
            pixel_mask[2::6, 3::6, 0] = True
            pixel_mask[3::6, 1::6, 0] = True
            pixel_mask[3::6, 5::6, 0] = True
            pixel_mask[4::6, 3::6, 0] = True

            # G
            pixel_mask[0::3, 0::3, 1] = True
            pixel_mask[1::3, 1::3, 1] = True
            pixel_mask[1::3, 2::3, 1] = True
            pixel_mask[2::3, 1::3, 1] = True
            pixel_mask[2::3, 2::3, 1] = True

            # B
            pixel_mask[0::6, 1::6, 2] = True
            pixel_mask[0::6, 5::6, 2] = True
            pixel_mask[1::6, 3::6, 2] = True
            pixel_mask[2::6, 0::6, 2] = True
            pixel_mask[3::6, 2::6, 2] = True
            pixel_mask[3::6, 4::6, 2] = True
            pixel_mask[4::6, 0::6, 2] = True
            pixel_mask[5::6, 3::6, 2] = True
        case _:
            raise ValueError("Invalid keyword 'cfa_type' value. Possible values: 'bayer', 'xtrans'")

    match interpolation_method:
        case 'nearest':
            interpolation = nearest_neighbour
        case 'linear':
            interpolation = linear
        case 'cubic':
            interpolation = cubic
        case _:
            raise ValueError("Invalid keyword 'interpolation' value. Possible values: 'nearest', 'linear', 'cubic'")

    height, width, channels = image.shape

    y_indices, x_indices = np.indices((height, width))

    demosaiced_image = np.zeros_like(image)
    demosaiced_image[pixel_mask] = image[pixel_mask]

    for c in range(channels):
        for coord in np.column_stack((y_indices[~pixel_mask[:, :, c]], x_indices[~pixel_mask[:, :, c]])):
            demosaiced_image[coord[0], coord[1], c] = interpolation(image, pixel_mask, coord, c)

    output_path = f"{output_dir}{cfa_type}_demosaiced_{interpolation_method}_image.png"
    cv2.imwrite(output_path, demosaiced_image)
    return output_path

if __name__ == '__main__':
    SRC_PATH = r"C:\Users\iwoch\PycharmProjects\PythonStuff\SiOC\image.png"
    OUT_PATH = "C:\\Users\\iwoch\\PycharmProjects\\PythonStuff\\SiOC\\cfa_img\\"
    BAYER_SRC_PATH = apply_cfa(SRC_PATH, OUT_PATH, 'bayer')
    XTRANS_SRC_PATH = apply_cfa(SRC_PATH, OUT_PATH, 'xtrans')
    start = time()
    print(f"\n{demosaicing_cfa(BAYER_SRC_PATH, OUT_PATH, 'bayer', interpolation_method='nearest')}\ntime={time()-start}s\n")
    start = time()
    print(f"{demosaicing_cfa(XTRANS_SRC_PATH, OUT_PATH, 'xtrans', interpolation_method='nearest')}\ntime={time()-start}s\n")
    start = time()
    print(f"{demosaicing_cfa(BAYER_SRC_PATH, OUT_PATH, 'bayer', interpolation_method='linear')}\ntime={time()-start}s\n")
    start = time()
    print(f"{demosaicing_cfa(XTRANS_SRC_PATH, OUT_PATH, 'xtrans', interpolation_method='linear')}\ntime={time()-start}s\n")
    start = time()
    print(f"{demosaicing_cfa(BAYER_SRC_PATH, OUT_PATH, 'bayer', interpolation_method='cubic')}\ntime={time()-start}s\n")
    start = time()
    print(f"{demosaicing_cfa(XTRANS_SRC_PATH, OUT_PATH, 'xtrans', interpolation_method='cubic')}\ntime={time()-start}s\n")


