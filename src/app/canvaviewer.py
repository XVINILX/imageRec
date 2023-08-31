from PyQt5.QtWidgets import QWidget, QTabWidget, QLineEdit, QLabel, QPushButton, QVBoxLayout, QMainWindow


class CanvaViewer(QMainWindow):
    def __init__(self):
        super().__init__()
        label = QLineEdit('Reconstruções')

        window = QWidget()

        layout = QVBoxLayout()
        tab = QTabWidget()
        button = QPushButton('Sinograma')
        button2 = QPushButton('BackProjection')
        tab.addTab(button, 'Sinograma')
        tab.addTab(button2, 'BackProjection')

        label = QLabel('Reconstruções')
        
        
        layout.addWidget(label)  
        layout.addWidget(tab)    
        window.setLayout(layout)
        self.setCentralWidget(window)
