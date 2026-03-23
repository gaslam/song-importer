import QtQuick
import QtQuick.Dialogs
import SongImporter.Utils
import SongImporter.Validators

Item {
    id:root
    FolderValidator{
    id:validator
    }

    FolderDialog{
        id:folderDialog


        onAccepted: {
            inputDialog.valueText = FileUtils.localPath(selectedFolder)
            inputDialog.startValidation()
        }
    }

    property string headerText:"folder location"
    property string buttonText:"Select"
    property string inputText: "c:/"
    property double minWidth: 250
    property bool isValid:false

    height: inputDialog.height

InputDialog{
    id:inputDialog
    headerText: root.headerText
    buttonText: root.buttonText
    minWidth: root.minWidth
    valueText: root.inputText

    onButtonClicked: {
        folderDialog.open()
    }
    onInputTextChanged: {
        startValidation();
    }

    function startValidation()
    {
        let result = validator.validate(inputDialog.valueText)
        if(!result.isSuccessful){
            setError(result.error)
        }
        else{
            clearError()
        }

        root.isValid = result.isSuccessful
    }
}


}
