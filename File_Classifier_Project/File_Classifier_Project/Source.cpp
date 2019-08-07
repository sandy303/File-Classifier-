#include <iostream>
#include "String"
#include <Vector>
using namespace std;

void classifyRecursively(string);

void classifyCurrentDirectory(string _rootDirectory);
void classifyRecursivelyKeep(string _rootDirectory);
void moveFilesToRoot(string _rootDirectory, string _currentDirectory);

vector<string> getFilesFromDirectory(string _rootDirectory);
vector<string> getSubdirectories(string _rootDirectory);
string getFileCategory(string _fileName);
// it takes the command  as an argument and then give it to the system , the function 
// returns the output that done by the system as result  from the command .
std::string exec(string _cmd)
{

	//converting _cmd to char array
	char *temp = new char[_cmd.size() + 1];
	strcpy(temp, _cmd.c_str());
	@@ - 46, 56 + 48, 53 @@ map<string, vector<string>> Data;
}

	int main(int argc, char **argv)
	{
		//example
		// string output = exec("ls");
		// cout << "Directory Content:\n"+ output;
		// cout << argc << endl;
		// for(int i = 0; i<argc; i++)
		// {
		//     cout << argv[i] << endl;./

		// }

		// data["music"] = {".mp3", ".wav"};
		// data["videos"] = {".mp4", ".mkv"};
		// data["documents"] = {".pdf", ".docx"};
		// data["images"] = {".png", ".jpeg"};

		Data["music"].push_back(".mp3");
		Data["videos"].push_back(".mkv");
		Data["documents"].push_back(".pdf");

		string option = argv[1];
		cout << argc << endl;
		if (argc == 2)
			if (argc == 1)
			{
				//default
				classifyCurrentDirectory(argv[1]);
				throw std::runtime_error("not enough arguments, use -help for usage info\n");
				return 1;
			}
			else if (argc == 2)
			{
				string arg1 = argv[1];
				if (arg1 == "-help")
				{
					ifstream inFile ;
					inFile.open("../documentation.txt");
					string line;
					while (getline(inFile, line))
						cout << line << endl;
				}
				else
				{
					classifyCurrentDirectory(argv[1]);
				}
			}
			else
			{

				classifyRecursivelyKeep(argv[1]);

				string option = argv[1];

				if (option == "-rk")
					classifyRecursivelyKeep(argv[2]);
				else if (option == "-rr")
				{
					moveFilesToRoot(argv[2], argv[2]);
					classifyCurrentDirectory(argv[2]);
				}
			}
		return 0;
	}


	/*
	testing:
	/home/undo/Development/Projects/FileClassifier/testingDir
	/home/undo/Desktop
	*/

	class Node
	{
	public:
		int cntNodes = 0;
		string selfPath;
		string parentPath;
		Node *children[];
	};

	vector<string> getFilesFromDirectory(string _rootDirectory)
	{
		string command = "";
		@@ - 174, 6 + 173, 7 @@ void classifyCurrentDirectory(string _rootDirectory)

			void classifyRecursivelyKeep(string _rootDirectory)
		{
			cout << _rootDirectory << endl;
			vector<string> subDirectories = getSubdirectories(_rootDirectory);
			for (auto subDirectory : subDirectories)
			{
				@@ - 182, 6 + 182, 38 @@ void classifyRecursivelyKeep(string _rootDirectory)
					classifyCurrentDirectory(_rootDirectory);
			}

			void moveFilesToRoot(string _rootDirectory, string _currentDirectory)
			{
				vector<string> subDirectories = getSubdirectories(_currentDirectory);
				cout << _rootDirectory << ": " << _currentDirectory << endl;
				for (auto subDirectory : subDirectories)
				{
					moveFilesToRoot(_rootDirectory, _currentDirectory + "/" + subDirectory);
				}
				vector<string> files = getFilesFromDirectory(_currentDirectory);
				for (auto file : files)
				{
					if (_currentDirectory != _rootDirectory)
					{
						string command = "";
						command += "mv ";
						command += _currentDirectory;
						command += "/";
						command += file;
						command += " ";
						command += _rootDirectory;
						exec(command);
					}
				}
				if (_currentDirectory != _rootDirectory)
				{
					string command = "";
					command += "cd .. && rm -d ";
					command += _currentDirectory;
					exec(command);
				}
			}

			vector<string> getSubdirectories(string _rootDirectory)
			{
				string command = "";
				@@ - 202, 123 + 234, 9 @@ vector<string> getSubdirectories(string _rootDirectory)
					while (commandOutput.find('\n') != string::npos)
					{
						string subDirectory = commandOutput.substr(0, commandOutput.find('\n'));
						subDirectory = subDirectory.substr(0, subDirectory.size() - 1);
						getSubdirectories.push_back(subDirectory);
						commandOutput = commandOutput.substr(commandOutput.find('\n') + 1, commandOutput.size());
					}
				return getSubdirectories;
			}

			/*
			string TypeOfFile(string s)
			{
				if (s == "mp3")
					return "music";
				else if (s == "mp4")
					return "video";
				else if (s == "png" || s == "jpg")
					return "image";
				else if (s == "txt")
					return "document";
				else
					return "not known";
			}
			vector<pair<string, string>> getContent(string _rootDir)
			{
				vector<pair<string, string>> ret;
				string cmd = "";
				cmd += "ls ";
				cmd += _rootDir;
				cmd += " -p ";
				cmd += "| grep -v /";
				char *temp = new char[cmd.size() + 1];
				strcpy(temp, cmd.c_str());
				string content = exec(temp);
				string tempContent = "";
				for (int i = 0; i < content.size(); i++)
				{
					if (content[i] != '\n')
						tempContent += content[i];
					else
					{
						string type = "";
						for (int j = 0; j < tempContent.size(); j++)
						{
							if (tempContent[j] == '.')
							{
								for (int k = j + 1; k < tempContent.size(); k++)
								{
									type += tempContent[k];
								}
							}
							else
							{
								continue;
							}
						}
						ret.push_back({_rootDir + tempContent, TypeOfFile(type)});
						tempContent = "";
						i += 1;
					}
				}
				return ret;
			}
			void classifyRecursively(string _rootDir)
			{
				string rootDir = _rootDir;
				// cout << rootDir << endl;
				Node *root = new Node();
				root->selfPath = rootDir;
				root->parentPath = " ";
				string cmd = "";
				cmd += "ls ";
				cmd += rootDir;
				cmd += " -p ";
				cmd += "| grep /";
				char *temp = new char[cmd.size() + 1];
				strcpy(temp, cmd.c_str());
				string children = exec(temp);
				int lastIndex = 0;
				//cout<<children.size();
				string tmp = "";
				for (int i = 0; i < children.size(); i++)
				{
					if (children[i] != '/')
					{
						tmp += children[i];
					}
					else
					{
						Node *child = new Node();
						child->parentPath = rootDir;
						child->selfPath = child->parentPath + "/" + tmp;
						root->children[root->cntNodes++] = child;
						tmp = "";
						i += 1;
					}
				}
				for (int i = 0; i < root->cntNodes; i++)
				{
					// cout << root->children[i]->selfPath << endl;
					vector<pair<string, string>> tmp = getContent(root->children[i]->selfPath);
					for (int j = 0; j < tmp.size(); j++)
					{
						cout << tmp[j].first << " " << tmp[j].second << endl;
					}
					classifyRecursively(root->children[i]->selfPath);
				}
				for (int i = 0; i < 5; i++)
				{
					vector<int> v;
					v.push_back(5);
				}
			}
			*/