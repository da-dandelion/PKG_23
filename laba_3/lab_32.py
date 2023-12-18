import tkinter as tk
from tkinter import filedialog

import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageTk


class ImageProcessor:

    def __init__(self) -> None:

        self.root = tk.Tk()
        self.root.title("Digital image processing")
        self.root.configure(bg='#65350f')
        
        self.default_image = np.zeros((300, 300, 3), dtype=np.uint8)
        self.default_image[:] = (255, 255, 255)

        self.image = None
        self.processed_image = None
        self.panel = tk.Label(self.root)
        self.panel.pack(side="right", padx=11, pady=20)

        self._setup_buttons()

# ----------оформление главного окна-----------
    def _setup_buttons(self) -> None:

        self.open_btn = tk.Button(
            self.root, text="Open Image", command=self.open_image
        )
        self.open_btn.config(bg = '#16a085', fg = "white")
        self.open_btn.config(font = ("Bookman Old Style", 15, "bold"))
        self.open_btn.pack(pady=15)

        self.points_btn = tk.Button(
            self.root, text="Show Points", command=self.show_points
        )
        self.points_btn.config(bg = '#16a085', fg = "white")
        self.points_btn.config(font = ("Arial", 10, "bold"))
        self.points_btn.pack(pady=15)

        self.edges_btn = tk.Button(
            self.root, text="Show Edges", command=self.show_edges
        )
        self.edges_btn.config(bg = '#16a085', fg = "white")
        self.edges_btn.config(font = ("Arial", 10, "bold"))
        self.edges_btn.pack(pady=15)

        self.linear_contrast_btn = tk.Button(
            self.root, text="Linear Contrast", command=self.linear_contrast
        )
        self.linear_contrast_btn.config(bg = '#16a085', fg = "white")
        self.linear_contrast_btn.config(font = ("Arial", 10, "bold"))
        self.linear_contrast_btn.pack(pady=15)

        self.negative_btn = tk.Button(
            self.root, text="Negative contrast", command=self.negative
        )
        self.negative_btn.config(bg = '#16a085', fg = "white")
        self.negative_btn.config(font = ("Arial", 10, "bold"))
        self.negative_btn.pack(pady=15)

        self.histogram_btn = tk.Button(
            self.root, text="Show Histogram", command=self.show_histogram
        )
        self.histogram_btn.config(bg = '#16a085', fg = "white")
        self.histogram_btn.config(font = ("Arial", 10, "bold"))
        self.histogram_btn.pack(pady=15)

        self.histogram_equalization_btn = tk.Button(
            self.root, text="Histogram Equalization", command=self.histogram_equalization
        )
        self.histogram_equalization_btn.config(bg = '#16a085', fg = "white")
        self.histogram_equalization_btn.config(font = ("Arial", 10, "bold"))
        self.histogram_equalization_btn.pack(pady=15)

        self.rgb_histogram_equalization_btn = tk.Button(
            self.root, text="RGB Histogram Equalization", command=self.rgb_histogram_equalization
        )
        self.rgb_histogram_equalization_btn.config(bg = '#16a085', fg = "white")
        self.rgb_histogram_equalization_btn.config(font = ("Arial", 10, "bold"))
        self.rgb_histogram_equalization_btn.pack(pady=15)

        #self.hsv_histogram_equalization_btn = tk.Button(
        #   self.root, text="HSV Histogram Equalization", command=self.hsv_histogram_equalization
        #)
        #self.hsv_histogram_equalization_btn.config(bg = '#16a085', fg = "white")
        #self.hsv_histogram_equalization_btn.config(font = ("Arial", 10, "bold"))
        #self.hsv_histogram_equalization_btn.pack(pady=15)

        self.gradient_btn = tk.Button(
            self.root, text="Show Gradient Magnitude", command=self.show_gradient_magnitude
        )
        self.gradient_btn.config(bg = '#16a085', fg = "white")
        self.gradient_btn.config(font = ("Arial", 10, "bold"))
        self.gradient_btn.pack(pady=15)

        self.original_btn = tk.Button(
        self.root, text="Show Original", command=self.show_original_image
        )
        self.original_btn.config(bg = '#16a085', fg = "white")
        self.original_btn.config(font = ("Bookman Old Style", 15, "bold"))
        self.original_btn.pack(pady=15)


# ------------изменение изображения------------
    def resize_image(self, image, width=None, height=None):
        h, w = image.shape[:2]

        if width is None and height is None:
            return image

        if width is None:
            aspect_ratio = height / h
            new_width = int(w * aspect_ratio)
            new_size = (new_width, height)
        else:
            aspect_ratio = width / w
            new_height = int(h * aspect_ratio)
            new_size = (width, new_height)

        resized_img = cv2.resize(image, new_size, interpolation=cv2.INTER_AREA)
        return resized_img


# ------------изменение изображения------------
    def open_image(self):
        file_path = filedialog.askopenfilename()

        if file_path:
            self.image = cv2.imread(file_path)
            self.processed_image = np.copy(self.image)
            self.display_image(self.processed_image)
        else:
            self.image = None
            self.processed_image = None
            self.display_image(self.default_image)



# -----------------------------исходное изображение без фильтров-----------------------------------
# создавая копию оригинального изображения и после выводя ее
    def show_original_image(self):
        if self.image is None:
            return
        self.processed_image = np.copy(self.image)
        self.display_image(self.processed_image)



# ---------обнаружение точек изображения-----------
    def show_points(self):
        if self.image is None:
            return

# перевод изображения в оттенки серого 
        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
# обнаружение границ на изображении - точек
        edges = cv2.Canny(gray, threshold1=50, threshold2=150, apertureSize=3)
# вычисление градиентов (изменение яркости) по осям x и y
        sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=5)
        sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=5)
# вычисление значения градиентов (изменение яркости) по осям x и y в нормальных пределах
        gradient_magnitude = cv2.magnitude(sobelx, sobely)
        gradient_magnitude = cv2.normalize(gradient_magnitude, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)

        all_points = cv2.bitwise_or(edges, gradient_magnitude)
        self.display_image(all_points)



    def show_gradient_magnitude(self):
        if self.image is None:
            return

        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)

#выявление границы и изменения яркости в изображении
        sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=5)
        sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=5)

        gradient_magnitude = cv2.magnitude(sobelx, sobely)
        gradient_magnitude = cv2.normalize(gradient_magnitude, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)
        self.display_image(gradient_magnitude)


# -------------------изображение границ изображения---------------
    def show_edges(self):
        if self.image is None:
            return
        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        edges = cv2.Canny(gray, threshold1=50, threshold2=150, apertureSize=3)
        self.display_image(edges)



# --------------------------------избражение-----------------------
    def display_image(self, img):
        img = self.resize_image(img, width=650, height=650)
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img = Image.fromarray(img)
        img = ImageTk.PhotoImage(image=img)
        self.panel.config(image=img)
        self.panel.image = img



 # построение гистограммы изображения
    def show_histogram(self) -> None:
        if self.image is None:
            return

        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        hist = cv2.calcHist([gray], [0], None, [256], [0, 256])

        plt.plot(hist)
        plt.title("Grayscale Histogram")
        plt.xlabel("Bins")
        plt.ylabel("# of Pixels")
        plt.show()


 # линейное контрастирование
    def linear_contrast(self) -> None:
        if self.image is None:
            return
# Функция выполняет линейное растяжение контраста на входном изображении. 
# Она масштабирует значения пикселей, чтобы они
# охватывали весь диапазон [0, 255], что способствует улучшению контраста.
    
#  находим минимальное и максимальное значение пикселей
        mn, mx = self.image.min(), self.image.max()
        result = (self.image - mn) / (mx - mn) * 255
# чтобы не выходило за диапазоны 0 - 255 -? обрезка значений пикселей        result = np.clip(result, 0, 255)
        self.display_image(result.astype(np.uint8))



# построение гистограммы изображения
    def histogram_equalization(self) -> None:
        if self.image is None:
            return
        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        equalized = cv2.equalizeHist(gray)
        self.processed_image = cv2.cvtColor(equalized, cv2.COLOR_GRAY2BGR)
        self.display_image(self.processed_image)


    def rgb_histogram_equalization(self) -> None:
        if self.image is None:
            return

        b, g, r = cv2.split(self.image)
        b_equalized = cv2.equalizeHist(b)
        g_equalized = cv2.equalizeHist(g)
        r_equalized = cv2.equalizeHist(r)

        equalized_image = cv2.merge((b_equalized, g_equalized, r_equalized))
        self.processed_image = equalized_image
        self.display_image(self.processed_image)



#   ------------- НЕГАТИВНОЕ ИЗОБРАЖЕНИЕ ----------------
    def negative(self) -> None:
# проверка на наличие изображения
        if self.image is None:
            return
# создается копия оригинального изображение. вычитание пикселя из 255 
# каждое значение пикселя становится инвертированным 
# и получаем цвето негативное изображение
        self.processed_image_neg = np.copy(255 - self.image)
        self.display_image(self.processed_image_neg)




    def hsv_histogram_equalization(self) -> None:
        if self.image is None:
            return

        hsv = cv2.cvtColor(self.image, cv2.COLOR_BGR2HSV)
        h, s, v = cv2.split(hsv)
        v_equalized = cv2.equalizeHist(v)
        hsv_equalized = cv2.merge((h, s, v_equalized))
        equalized_image = cv2.cvtColor(hsv_equalized, cv2.COLOR_HSV2BGR)
        self.processed_image = equalized_image
        self.display_image(self.processed_image)



    def run(self) -> None:
        self.display_image(self.default_image)
        self.root.mainloop()


def main() -> None:
    processor = ImageProcessor()
    processor.run()
 

if __name__ == "__main__":
    main()
