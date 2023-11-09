/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "News/Domain/Model/Gs2NewsEzNewsGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2NewsNews.generated.h"

USTRUCT(BlueprintType)
struct FGs2NewsOwnNews
{
    GENERATED_BODY()

    Gs2::UE5::News::Domain::Model::FEzNewsGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2NewsNewsValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Section = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Content = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Title = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ScheduleEventId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Timestamp = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString FrontMatter = "";
};

inline FGs2NewsNewsValue EzNewsToFGs2NewsNewsValue(
    const Gs2::UE5::News::Model::FEzNewsPtr Model
)
{
    FGs2NewsNewsValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2NewsNewsFunctionLibrary::EzNewsToFGs2NewsNewsValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Section = Model->GetSection() ? *Model->GetSection() : "";
    Value.Content = Model->GetContent() ? *Model->GetContent() : "";
    Value.Title = Model->GetTitle() ? *Model->GetTitle() : "";
    Value.ScheduleEventId = Model->GetScheduleEventId() ? *Model->GetScheduleEventId() : "";
    Value.Timestamp = Model->GetTimestamp() ? *Model->GetTimestamp() : 0;
    Value.FrontMatter = Model->GetFrontMatter() ? *Model->GetFrontMatter() : "";
    return Value;
}

inline Gs2::UE5::News::Model::FEzNewsPtr FGs2NewsNewsValueToEzNews(
    const FGs2NewsNewsValue Model
)
{
    return MakeShared<Gs2::UE5::News::Model::FEzNews>()
        ->WithSection(Model.Section)
        ->WithContent(Model.Content)
        ->WithTitle(Model.Title)
        ->WithScheduleEventId(Model.ScheduleEventId)
        ->WithTimestamp(Model.Timestamp)
        ->WithFrontMatter(Model.FrontMatter);
}

UCLASS()
class BPGS2_API UGs2NewsNewsFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};