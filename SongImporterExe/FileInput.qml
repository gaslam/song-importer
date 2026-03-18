import QtQuick
import SongImporter.Validators

Item {
    id:root
    FileValidator{
        id:validator
        supportedFileTypes: ["xml"]
    }

    InputDialog{
        id:inputDialog
        headerText: "Export xml file location"
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
