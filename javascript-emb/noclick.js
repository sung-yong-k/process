var xmlDom = new ActiveXObject("Microsoft.XMLDOM");
var el = xmlDom.createElement("tmp");
el.dataType = "bin.Base64";
el.text = "cG93ZXJzaGVsbC5leGUgU3RhcnQtUHJvY2VzcyBjYWxj";

// Use a binary stream to write the bytes into
var strm = WScript.CreateObject("ADODB.Stream");
strm.Type = 1; // Binary
strm.Open();
strm.Write(el.nodeTypedValue);

// Revert to the start of the stream and convert output to utf-8
strm.Position = 0;
strm.Type = 2; // Text
strm.CharSet = "utf-8";
var decodedCommand = strm.ReadText(); // Read decoded command

// Output the textual equivalent of the decoded byte array
WScript.Echo(decodedCommand); // Should display the decoded command

// Run the decoded command
var shell = new ActiveXObject("WScript.Shell");
shell.Run(decodedCommand); // Pass the string directly

strm.Close();
