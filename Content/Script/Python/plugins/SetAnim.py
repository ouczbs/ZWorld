import unreal
import os
path = "/Game/ALS/Animations"
EditAssetLib = unreal.EditorAssetLibrary()
#root = unreal.EditorAssetLibrary.get_path_name("/Game")
rel_dir = unreal.Paths.project_content_dir()
real_path = path.replace("/Game", rel_dir)

def run_default(_dir , _file):
    print(_dir , _file)
def forwalk(root, rel_dir , callback = run_default):
    for parent,dir_names,file_names in os.walk(root):
        rel_parent = parent.replace(rel_dir,"/Game")
        for file_name in file_names:
            callback(rel_parent, file_name)
        pass
    pass
def run_anim(_dir , _file):
    #获取操作函数库
    name = _dir + "/" + _file[:-7]
    anim_data = EditAssetLib.find_asset_data(name)
    anim_class = anim_data.asset_class
    anim_asset = anim_data.get_asset()
    if anim_class == "AnimMontage":
        res = unreal.AnimMontage.cast(anim_asset)
    elif anim_class == "AnimSequence":
        pass
    else:
        print(name)
    ##res = unreal.AnimSequence.cast(anim_data.get_asset())
forwalk(real_path, rel_dir, run_anim)
print(real_path)
#unreal.EditorAssetLibrary.
#unreal.AnimSequence.set_preview_skeletal_mesh()