#!/bin/bash     
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
GIT=".git"
DIRECTORY="$DIR/$GIT"

# our current feature branch can be overridden using a third parameter.
if [ -z "$3" ]
	then
		FEATUREBRANCH='feature/NEWSROOM-Multilingual'
	else
		FEATUREBRANCH="$3"
fi

# ask the user for confirmation, this is a delicate operation.
read -t 10 -p "Your feature branch is $FEATUREBRANCH, can you confirm, please? " -n 1 -r
echo
if [[ $REPLY != [Nn] ]]
  then
		if [ $# -eq 2 ]
			then
				# If we have user and password we set some configs.
				GITUSER="$1"
				GITPASSWORD="$2"
				git config --global github.user "$USER"
				git config --global credential.helper cache
			else
				GITUSER=""
				GITPASSWORD=""
		fi

		# check if we are in the root of the project.
		if [ -d "$DIRECTORY" ] 
			then
				# Get the origin URL of the repo from git.
				URL=$(git config --get remote.origin.url) 
				PUSH=${URL#*//}
		  	git fetch upstream
		  	git checkout develop
				git rebase upstream/develop
				
				if [ ! -z "$GITUSER" ]
					then
						git push --repo https://"$GITUSER":"$GITPASSWORD"@"$PUSH"
					else
						git push
				fi
				
				git checkout "$FEATUREBRANCH"
				git fetch origin develop
				git merge FETCH_HEAD -m "Syncing our feature branch"
				git push  --repo https://"$GITUSER":"$GITPASSWORD"@"$PUSH"

		else
			echo "It seems that you're not in the root of your project, please fix this."
	fi
else
	exit
fi