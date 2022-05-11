from PIL import Image

import os

for item in os.listdir("./"):
    if ".png" in item:
        img = Image.open(item)

        n_im = Image.new("RGBA", (img.width, img.height))

        for r in range(img.width):
            for c in range(img.height):
                
                a = img.getpixel((r, c))
                if type(a) == tuple:
                    alpha = a[3]
                    n_im.putpixel((r, c), (alpha, alpha, alpha, alpha))
                else:
                    n_im.putpixel((r, c), (a, a, a, a))
        img.close()
        print(item)
        n_im.save(item)
        