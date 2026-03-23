import QtQuick
import SongImporter.Validators
import QtQuick.Dialogs

Item {
    id:root
    property var fileGroups: (
                                 [{
                                      "name": "XML files",
                                      "fileTypes": ["xml"]
                                  }])

    property string headerText:"file location"
    property string buttonText:"Select"
    property string inputText:"example.xml"
    property double minWidth: 250
    property bool isValid:false

    FileDialog{
        id:fileDialog
        nameFilters: {
            let filters = []

            // Iterate each group in fileGroups
            for (let i = 0; i < root.fileGroups.length; i++) {
                let group = root.fileGroups[i]
                let pattern = ""

                // Build pattern like *.mp3 *.wav ...
                for (let j = 0; j < group.fileTypes.length; j++) {
                    pattern += "*." + group.fileTypes[j].toLowerCase() + " "
                }

                // Add group filter
                filters.push(group.name + " (" + pattern.trim() + ")")
            }

            return filters
        }


        onAccepted: {

            inputDialog.valueText = FileUtils.localPath(selectedFile)
            inputDialog.startValidation()
        }
    }

    FileValidator{
        id:validator
    }

    height: inputDialog.height

    InputDialog{
        id:inputDialog
        headerText: root.headerText
        buttonText: root.buttonText
        minWidth: root.minWidth
        valueText: root.inputText

        onButtonClicked: {
            fileDialog.open();
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
            isValid = result.isSuccessful;
        }
    }
    Component.onCompleted: {
        let types = []

        for (let i = 0; i < root.fileGroups.length; i++) {
            let group = root.fileGroups[i]

            for (let j = 0; j < group.fileTypes.length; j++) {
                types.push(group.fileTypes[j])
            }
        }

        // Assign the array to QStringList property
        validator.supportedFileTypes = types
    }

}
