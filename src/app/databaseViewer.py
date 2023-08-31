from PyQt5.QtWidgets import QWidget, QPushButton, QVBoxLayout


class DataBaseViewer(QWidget):
    def __init__(self):
        super().__init__()

        layout = QVBoxLayout()

        label = QPushButton('label')
        self.setLayout(layout)
        layout.addWidget(label)        
