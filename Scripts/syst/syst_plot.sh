mkdir -p Systematics/ROOTFiles
cd Systematics
cp ../19062018/*syst*.root ./ROOTFiles
cp ../19062018/*hadrecoil*.root ./ROOTFiles
python ../plot_systematics.py
