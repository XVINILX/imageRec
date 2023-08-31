from PyQt5.QtWidgets import QWidget, QApplication, QMainWindow, QHBoxLayout, QLabel, QVBoxLayout, QGridLayout
from PyQt5 import QtWidgets
from output import Ui_GIMNRec
from canvaviewer import CanvaViewer
from openFile import OpenFile
from databaseViewer import DataBaseViewer

# Only needed for access to command line arguments
import sys

import os

# https://stackoverflow.com/questions/38606372/skimage-how-to-show-image
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("GIMN APP")
        self.resize(720,640)

        layout = QGridLayout()

        widgetCanvaViewer = CanvaViewer()
        widgetDataBaseViewer = DataBaseViewer()
        openFile = OpenFile()

        window2 = QWidget()
        layout2 = QHBoxLayout()

        layout2.addWidget(widgetCanvaViewer)
        layout2.addWidget(widgetDataBaseViewer)
        window2.setLayout(layout2)

        window = QWidget()
        layout.addWidget(openFile, 1, 1, 1, 1)
        layout.addWidget(window2, 2, 1, 3, 1)
        


        window.setLayout(layout)
        self.setCentralWidget(window)



app = QApplication(sys.argv)

window = MainWindow()

window.show()  # IMPORTANT!!!!! Windows are hidden by default.

# Start the event loop.
app.exec()

