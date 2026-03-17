import QtQuick
import SongImporter.Validators

Item {
    id:root
    FolderValidator{
    id:validator
    }

InputDialog{
    id:inputDialog
    headerText: "Export location"
    onButtonClicked: {
        startValidation();
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
    }
}


}
