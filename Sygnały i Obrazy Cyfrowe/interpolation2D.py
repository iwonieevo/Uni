import numpy as np
import cv2
from time import time


def nearest_neighbour_2d(mesh, to_interpolate):
    crds = np.clip(np.round(to_interpolate).astype(int), 0, np.array(mesh.shape[:2]) - 1)
    return (mesh[crds[..., 0], crds[..., 1]]).astype(np.uint8)

def linear_2d(mesh, to_interpolate):
    crds_floor = np.floor(to_interpolate).astype(int)
    x0 = np.clip(crds_floor[..., 1], 0, mesh.shape[1] - 1)
    y0 = np.clip(crds_floor[..., 0], 0, mesh.shape[0] - 1)
    x1 = np.clip(crds_floor[..., 1] + 1, 0, mesh.shape[1] - 1)
    y1 = np.clip(crds_floor[..., 0] + 1, 0, mesh.shape[0] - 1)
    weights = to_interpolate - crds_floor

    top_row = mesh[y0, x0, :] * (1 - weights[..., 1, None]) + mesh[y0, x1, :] * weights[..., 1, None]
    bottom_row = mesh[y1, x0, :] * (1 - weights[..., 1, None]) + mesh[y1, x1, :] * weights[..., 1, None]

    return (top_row * (1 - weights[..., 0, None]) + bottom_row * weights[..., 0, None]).astype(np.uint8)

def cubic_2d(mesh, to_interpolate):
    def cubic_kernel(d, a=-0.5):
        d = np.abs(d)
        result = np.zeros_like(d, dtype=np.float64)
        mask1 = d <= 1
        mask2 = (d < 2) & (d > 1)

        result[mask1] = (a + 2) * (d[mask1] ** 3) - (a + 3) * (d[mask1] ** 2) + 1
        result[mask2] = (a * (d[mask2] ** 3) - 5 * a * (d[mask2] ** 2) + 8 * a * d[mask2] - 4 * a)

        return result

    crds_floor = np.floor(to_interpolate).astype(int)
    output = np.zeros((to_interpolate.shape[0], to_interpolate.shape[1], mesh.shape[2]), dtype=np.float64)

    offsets = np.array([[-1, -1], [-1, 0], [-1, 1], [-1, 2],
                        [0, -1], [0, 0], [0, 1], [0, 2],
                        [1, -1], [1, 0], [1, 1], [1, 2],
                        [2, -1], [2, 0], [2, 1], [2, 2]])

    for n_offset, m_offset in offsets:
        y = np.clip(crds_floor[..., 0] + n_offset, 0, mesh.shape[0] - 1)
        x = np.clip(crds_floor[..., 1] + m_offset, 0, mesh.shape[1] - 1)

        output += mesh[y, x] * cubic_kernel(to_interpolate[..., 0] - y)[..., None] * cubic_kernel(to_interpolate[..., 1] - x)[..., None]

    return np.clip(output, 0, 255).astype(np.uint8)

def modify_image(image, method='nearest', angle=0, scale=1.0, frame_val=None):
    if frame_val is None:
        frame_val = [0, 0, 0]

    funcs = {'nearest': nearest_neighbour_2d,
             'linear': linear_2d,
             'cubic': cubic_2d}
    interpolation = funcs.get(method, 'nearest')

    if angle != 0:
        height, width, channels = image.shape
        theta = np.radians(angle)
        new_height = int(abs(height * np.cos(theta)) + abs(width * np.sin(theta)))
        new_width = int(abs(width * np.cos(theta)) + abs(height * np.sin(theta)))

        y_indices, x_indices = np.indices((new_height, new_width))

        new_x = (x_indices - new_width // 2) * np.cos(theta) + (y_indices - new_height // 2) * np.sin(theta) + width // 2
        new_y = -(x_indices - new_width // 2) * np.sin(theta) + (y_indices - new_height // 2) * np.cos(theta) + height // 2

        coordinates = np.stack((new_y, new_x), axis=-1)

        valid = (coordinates[..., 0] >= 0) & (coordinates[..., 0] < height) & (coordinates[..., 1] >= 0) & (coordinates[..., 1] < width)

        image = interpolation(image, coordinates)
        image = np.where(valid[..., None], image, frame_val)

        if not np.all(image == frame_val):
            frame = np.all(image == frame_val, axis=-1)
            rows = np.any(~frame, axis=1)
            cols = np.any(~frame, axis=0)

            top = np.argmax(rows) if np.any(rows) else 0
            bottom = len(rows) - 1 - np.argmax(rows[::-1]) if np.any(rows) else image.shape[0] - 1
            left = np.argmax(cols) if np.any(cols) else 0
            right = len(cols) - 1 - np.argmax(cols[::-1]) if np.any(cols) else image.shape[1] - 1

            image = image[top:bottom + 1, left:right + 1]


    if scale != 1:
        height, width, channels = image.shape
        y = np.linspace(0, height - 1, int(height * scale))
        x = np.linspace(0, width - 1, int(width * scale))
        coordinates = np.stack(np.meshgrid(x, y), axis=-1)

        image = interpolation(image, coordinates)

    return image

def main_loop(image_to_modify, _method, output_path, border):
    print(f"\nStarting program using {_method} interpolation...")
    start = time()
    up_scaled_image = image_to_modify
    down_scaled_image = image_to_modify
    rotated_image = image_to_modify
    for i in range(5):
        print(f"Up-scaling image, {i=}")
        up_scaled_image = modify_image(up_scaled_image, method=_method, scale=1.1, frame_val=border)
    print(f"Scaling image back to normal")
    up_scaled_image = modify_image(up_scaled_image, method=_method, scale=(1.1 ** (-5)), frame_val=border)
    cv2.imwrite(f"{output_path}up-scaled_{_method}.png", up_scaled_image)

    for i in range(3):
        print(f"Down-scaling image, {i=}")
        down_scaled_image = modify_image(down_scaled_image, method=_method, scale=0.9, frame_val=border)
    print(f"Scaling image back to normal")
    down_scaled_image = modify_image(down_scaled_image, method=_method, scale=(0.9 ** (-3)), frame_val=border)
    cv2.imwrite(f"{output_path}down-scaled_{_method}.png", down_scaled_image)

    for i in range(30):
        print(f"Rotating image, {i=}")
        rotated_image = modify_image(rotated_image, method=_method, angle=12, frame_val=border)
    cv2.imwrite(f"{output_path}rotated_{_method}.png", rotated_image)

    print(f"Generating reference image...")
    cv2.imwrite(f"{output_path}reference_{_method}.png", modify_image(image_to_modify, method=_method, scale=1.5, angle=30, frame_val=border))
    end = time()
    return end - start


if __name__ == '__main__':
    SRC_PATH = r"/SiOC/image.png"
    OUT_PATH = "/SiOC/scaled_rotated_img\\"
    SRC = cv2.imread(SRC_PATH)
    if SRC is None:
        raise ValueError("Image not found or unable to load.")
    FRAME_COLOUR = [0, 0, 0]

    t_nearest = main_loop(SRC, 'nearest', OUT_PATH, FRAME_COLOUR)
    t_linear = main_loop(SRC, 'linear', OUT_PATH, FRAME_COLOUR)
    t_cubic = main_loop(SRC, 'cubic', OUT_PATH, FRAME_COLOUR)
    print(
        f"Using nearest neighbor interpolation took {t_nearest}s to complete\n"
        f"Using linear interpolation took {t_linear}s to complete\n"
        f"Using cubic interpolation took {t_cubic}s to complete\n"
    )



