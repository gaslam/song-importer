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
    property double minWidth: 250
    property bool isValid:false

InputDialog{
    id:inputDialog
    headerText: root.headerText
    buttonText: root.buttonText
    minWidth: root.minWidth

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
