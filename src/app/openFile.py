from PyQt5.QtWidgets import QWidget, QPushButton, QHBoxLayout, QFileDialog, QLineEdit, QGridLayout

import subprocess


class OpenFile(QWidget):
    def __init__(self):
        super().__init__()

        layout = QHBoxLayout()
        self.textEdit = QLineEdit()
        self.textEdit.baseSize()

        button = QPushButton("Abra um arquivo")
        button.clicked.connect(self.the_button_was_clicked)

        self.setLayout(layout)
        layout.addWidget(button)        
        layout.addWidget(self.textEdit)

    def the_button_was_clicked(self):
        fname = QFileDialog.getOpenFileName(self, "Open File", "", "All Files(*)")
        
        if fname:
            
            result = subprocess.Popen(['../../build/ImageRec', str(fname[0])])
            if(result):
                print(result.stdout)
           
            self.textEdit.setText(str(fname[0]))
