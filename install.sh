sudo ln -Pf pyclean /usr/bin/pyclean
sudo ln -Pf vimclean /usr/bin/vimclean
sudo ln -Pf dict /usr/bin/dict

gcc src/encryptx.c -o encryptx
sudo ln -Pf encryptx /usr/bin/encryptx
