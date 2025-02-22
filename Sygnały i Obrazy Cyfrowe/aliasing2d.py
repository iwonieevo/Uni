from numpy import linspace, pi, sin, abs
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter
from PIL import Image
from os import remove


def aliasing_2d(n=5, jump=16, px=256, K=64):
    K = max(K, int(px / jump))
    '''
    n - number of wings
    jump - number of lines, that the sensor reads from each frame
    K - number of frames - for the gif and for generating the shutter_effect image

    K >= int(px/jump) - because for the lower value, the shutter_effect image wouldn't be complete
    '''
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'}, figsize=(px / 96 - 0.1, px / 96 - 0.1))  # 1 inch == 96px
    line, = ax.plot([], [], lw=2)
    ax.set_axis_off()
    shutter_effect = Image.new('RGB', (px, px))

    theta = linspace(0, (2 * pi), 1000)

    def animate(m):
        if n % 2 == 1:
            r = sin(n * theta + m * pi / 10)
        else:
            r = abs(sin(int(n / 2) * theta + m * pi / 10)) ** 6
        '''
                the formula for graphing a shutter is different for even and odd n
                for even n, the first formula would actually graph twice as many wings than it should
                so the solution was to graph n/2 wings and then double it by using absolute value
                raising function to power, makes wings longer and more narrow 
        '''
        line.set_data(theta, r)

        temp = m + int(K / 2)  # 0, 1, 2..., K-1
        if temp * jump < px:
            '''
            after the shutter_effect image is complete, it will stop adding lines to the image, 
            that extend over the borders

            e.g. if jump=16, then the number of frames actually used to create a shutter_effect image is only 16 and if
            K=64, the code below would execute 48 extra times - without any effect (only slowing down the whole process)
            '''
            plt.savefig('t_frame.png')
            temp_img = Image.open('t_frame.png')
            temp_crop = temp_img.crop((0, temp * jump, px, temp * jump + jump))  # left, upper, right, lower
            shutter_effect.paste(temp_crop, (0, temp * jump))  # img_to_paste, (upper_left_column, upper_left_row)
            remove("t_frame.png")

        return line,

    animation = FuncAnimation(fig, animate, range(-int(K / 2), int(K / 2), 1), interval=50, blit=False)
    animation.save(f"rolling_shutter_{n}_wings_{K}_frames.gif", writer=PillowWriter(fps=28))
    shutter_effect.save(f"shutter_effect_{n}_wings_{jump}_lines.png")


if __name__ == '__main__':
    aliasing_2d()
