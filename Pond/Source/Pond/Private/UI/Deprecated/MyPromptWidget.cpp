// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Deprecated/MyPromptWidget.h"

bool UMyPromptWidget::PlayAnimationByName(FName AnimName)
{
    UWidgetAnimation* AnimationToPlay = nullptr;
    if(AnimName == "FadeIn")
        AnimationToPlay = FadeIn;
    else if(AnimName == "FadeOut")
        AnimationToPlay = FadeOut;
    PlayAnimation(AnimationToPlay);
    if(AnimationToPlay == nullptr)
        return false;
    return true;
}