// Global variable
var oldResponseText;
var oldCounter;
var bPaused = false;
var readLocation = "/home/admin1/Lawoo/Sample_Codes/Server_Client/New_Themes/"; //"http://192.168.0.230/New_Themes/"; //
var welcomeImagePath = readLocation + "TerumoBCTLogo.jpg";
var clientInputResponseFile = "ClientInput.txt";
var countervalue = "dump.txt";

var getImagePath=function()
{
	return welcomeImagePath;
}

//On loead html page 

//function onLoadOrion()
//{
//	myVar = setTimeout(readTextFile, 1);

//}

function increamentCounter(folderPath)
{
	//alert("counter method call");
	if(bPaused == false)
	{
		var rawFile = new XMLHttpRequest();
    		var file = folderPath + countervalue; 

    		rawFile.open("GET", file, true);
		rawFile.onreadystatechange = function ()
    		{
        		if(rawFile.readyState === 4)
        		{
            			if(rawFile.status === 200 || rawFile.status == 0)
            			{
					if(oldCounter !== rawFile.responseText)
					{
						oldCounter = rawFile.responseText;

						//alert("counter value=" + oldCounter);
						var lines = oldCounter.split("\n");

						if(lines[0] != undefined)
						{
							var textbox = document.getElementById("Counter_Value");
							textbox.value = lines[0];
						}
					}
				}
			}
		}
		rawFile.send();
	}	
}

//Pause button operation

function togglePause()
{
	bPaused = !bPaused;
	var button = document.getElementById("Pause_ID");
	if(bPaused == false)
	{
		button.innerHTML = "Pause";
	}
	else
	{
		button.innerHTML = "Paused";
	}
}


// Read raw file and updated page accordingly
// TODO:Change the logic based on inputs from user
function readInputTextFile(folderPath)
{
    if(bPaused == false)
   {
       var rawFile = new XMLHttpRequest();
       var file = folderPath + clientInputResponseFile; 

       rawFile.open("GET", file, true);
    
       rawFile.onreadystatechange = function ()
       {
           if(rawFile.readyState === 4)
           {
               if(rawFile.status === 200 || rawFile.status == 0)
               {
		// Due to less time refresh, it may happen that we are reading same input multiple times
		// Making sure that we are not updating reponse all the time
		  if(oldResponseText !== rawFile.responseText)
		  {
			oldResponseText = rawFile.responseText;
			lines = oldResponseText.split("\n");
			
			for(index = 0; index < lines.length; index++)
			{
				inputs = lines[index].split(" ");
				// parse depending upon type of input
				if(inputs[0] === "Motor")
				{
					// Motor input string: Type MotorName Status SpeedValue Unit
					updateMotorDataById(inputs[1], inputs[2], inputs[3], inputs[4])
				}
				else if(inputs[0] === "Sensor")
				{
					// Sensor input string: Type SensorName Status
					updateSensorStatusById(inputs[1],inputs[2]);
					updateSensorIndicatorById(inputs[1],inputs[2]);
				}
				else if(inputs[0] === "Alarm")
				{
					// Alarm input string: Type AlarmName Status
					updateAlarmStatusById(inputs[1],inputs[2]);
					updateAlarmIndicatorById(inputs[1],inputs[2]);
				}
				else if(inputs[0] === "Operation")
				{
					updateTextFieldById( inputs[1] + "_Status",inputs[2]);
				}
			}
		}		
            }
        }
    }   
   
    rawFile.send();
  }
}

// read text file method called once page is loaded
function readTextFile()
{
    //alert("readTextFile");
    // refresh data on page every 1 msec
    setInterval(function(){readInputTextFile(readLocation); }, 1);
    // refresh data on page every 500 msec
    setInterval(function(){increamentCounter(readLocation); }, 500);
}

// Checkbox toggle implementation
function toggleCheckBox(checkBoxId)
{
	var checkbox = document.getElementById(checkBoxId);

	checkbox.checked = !(checkbox.checked);
	checkbox.click();
}

// Method to chage hide/show state of HTML element
function showHideToggleElement(element)
{
	if(element.style.display === "none")
	{
		element.style.display = "block";
	}
	else
	{
		element.style.display = "none";
	}
}

// Method to update indicator status of element based on status
function updateIndicatorDisplayById(elementId, status)
{
	if(status === "ON" || status === "Activated")
	{
		var elementRedIndicator = document.getElementById(elementId + "_RedIndicator");
		if(elementRedIndicator.style.display === "none")
		{
			showHideToggleElement(elementRedIndicator);
		}

		var elementGreenIndicator = document.getElementById(elementId + "_GreenIndicator");
		if(elementGreenIndicator.style.display === "block")
		{
			showHideToggleElement(elementGreenIndicator);
		}		
	}
	else
	{
		var elementRedIndicator = document.getElementById(elementId + "_RedIndicator");	
			
		if(elementRedIndicator.style.display === "block")
		{
			showHideToggleElement(elementRedIndicator);
		}

		var elementGreenIndicator = document.getElementById(elementId + "_GreenIndicator");			
		if(elementGreenIndicator.style.display === "none")
		{
			showHideToggleElement(elementGreenIndicator);
		}
	}
}

// Method to update value of textfield element
function updateTextFieldById(textFieldId, text)
{
	var textField = document.getElementById(textFieldId);
	if(textField != undefined)
	{
		textField.value = text;
		if(text === "Normal")
		{
			textField.style.color = "Green";
		}
		else
		{
			textField.style.color = "Red";
		}
	}
}

// Method to update motor status
function updateMotorStatusById(motorId, status)
{
	var motorField = document.getElementById(motorId + "_Status");
	if(motorField != undefined)
	{
		motorField.value = status;
	}
}

// Method to update motor speed and units
function updateMotorDataById(motorId, status, speed, unit)
{
	var motorSpeedField = document.getElementById(motorId + "_SpeedValue");
	if(motorSpeedField != undefined)
	{
		motorSpeedField.value = speed;
	}	

	var motorSpeedUnitField = document.getElementById(motorId + "_SpeedUnit");
	if(motorSpeedUnitField != undefined)
	{
		motorSpeedUnitField.value = unit;
	}

	var motorField = document.getElementById(motorId+ "_Status");
	if(motorField != undefined)
	{
		motorField.value = status;
	}
}

// Method to update sensor status
function updateSensorStatusById(sensorId, status)
{
	var sensorField = document.getElementById(sensorId+ "_Status");
	if(sensorField != undefined)
	{
		sensorField.value = status;
		if(status != "OFF")
		{
			sensorField.style.color = "Red";
		}
		else
		{
			sensorField.style.color = "Black";
		}
	}
}

// Method to update sensor Indicator status
function updateSensorIndicatorById(sensorId, status)
{
	updateIndicatorDisplayById(sensorId, status);
}

// Method to update alarm status
function updateAlarmStatusById(alarmId, status)
{
	var alarmField = document.getElementById(alarmId+ "_Status");

	if(alarmField != undefined)
	{
		alarmField.value = status;
		if(status != "OFF")
		{
			alarmField.style.color = "Red";
		}
		else
		{
			alarmField.style.color = "Black";
		}
	}
}

// Method to update alarm indicator status
function updateAlarmIndicatorById(alarmId, status)
{
	updateIndicatorDisplayById(alarmId, status);
}
