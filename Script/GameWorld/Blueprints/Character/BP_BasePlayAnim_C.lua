--GameWorld.Blueprints.Character.BP_BasePlayAnim_C
--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

local class = Class()

--function class:Initialize(Initializer)
--end
--function class:BlueprintInitializeAnimation()
--end
--[[
    local function printPose(Pose , black)
    print(Pose)
    print(black , "Pose: " , Pose.LinkID , Pose.SourceLinkID)
end
local function printRootNode(Node)
    print(Node)
    print("Root Node: " , Node.Name)
    if Node.Result then
        printPose(Node.Result , "\t")
    end
end
local function printOverLayNode(Node)
    print(Node)
    print("Root Node: " , Node.Name)
    if Node.BasePose then 
        print("\tOverLay")
        printPose(Node.BasePose , "\t")
    end
    if Node.BlendPoses then 
        local num = Node.BlendPoses:Length()
        print("\tBlendPoses " , num)
        for i = 1 , num do 
            printPose(Node.BlendPoses:Get(i) , "\t\t")
        end
    end
    
end
function class:BlueprintBeginPlay()
    local MainNode = self.AnimNode_MemberRoot
    local OverLayNode = self.AnimNode_MemberOverLayBlend
    local AdditiveNode = self.AnimNode_MemberAdditiveBlend
    print(self, self.Object)
    printRootNode(MainNode)
    printOverLayNode(OverLayNode)
    printOverLayNode(AdditiveNode)
    local RunMainNode = self.AnimNode_ClimbingLayer
    local RunOverLayNode = self.AnimNode_OverLayBox
    --self:LinkNodePose(MainNode , RunMainNode);
    --self:LinkNodePose(MainNode , RunMainNode);
    --self:LinkNodePose(OverLayNode , RunOverLayNode);
    printRootNode(RunMainNode)
    printOverLayNode(RunOverLayNode)
    --self:LinkNodePose(OverMainNode , MainNode)
    --self:LinkNodePose(RootNode , OverlayNode)
    --UE4.UGameAnimLibrary.UpdateMemberRoot(obj.AnimNode_MainPose , self.AnimNode_ClimbingLayer.Result)
    --UE4.UGameAnimLibrary.UpdateMemberRoot(self.AnimNode_MemberRoot , self.AnimNode_ClimbingLayer.Result)
    --obj.AnimNode_MainPose.Result = self.AnimNode_ClimbingLayer.Result
    --self.AnimNode_MemberRoot.Result = obj.AnimNode_OverlayBox.Result 
    --local Pose = obj.AnimNode_MemberRoot.Result 
    --UE4.UGameAnimLibrary.UpdateMemberRoot(self.AnimNode_MemberRoot , Pose)
    --print(self:AnimGraph(self.AnimGraphNode_Root_1.Result))
end
]]


--function class:BlueprintUpdateAnimation(DeltaTimeX)
--end

-- function class:BlueprintPostEvaluateAnimation()
-- end

return class
