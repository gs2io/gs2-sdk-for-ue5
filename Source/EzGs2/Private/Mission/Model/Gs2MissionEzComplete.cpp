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

#include "EzGs2/Public/Mission/Model/Gs2MissionEzComplete.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzComplete> FEzComplete::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FEzComplete> FEzComplete::WithCompletedMissionTaskNames(
        const TSharedPtr<TArray<FString>> CompletedMissionTaskNames
    )
    {
        this->CompletedMissionTaskNamesValue = CompletedMissionTaskNames;
        return SharedThis(this);
    }

    TSharedPtr<FEzComplete> FEzComplete::WithReceivedMissionTaskNames(
        const TSharedPtr<TArray<FString>> ReceivedMissionTaskNames
    )
    {
        this->ReceivedMissionTaskNamesValue = ReceivedMissionTaskNames;
        return SharedThis(this);
    }
    TOptional<FString> FEzComplete::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }
    TSharedPtr<TArray<FString>> FEzComplete::GetCompletedMissionTaskNames() const
    {
        return CompletedMissionTaskNamesValue;
    }
    TSharedPtr<TArray<FString>> FEzComplete::GetReceivedMissionTaskNames() const
    {
        return ReceivedMissionTaskNamesValue;
    }

    Gs2::Mission::Model::FCompletePtr FEzComplete::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FComplete>()
            ->WithMissionGroupName(MissionGroupNameValue)
            ->WithCompletedMissionTaskNames(CompletedMissionTaskNamesValue)
            ->WithReceivedMissionTaskNames(ReceivedMissionTaskNamesValue);
    }

    TSharedPtr<FEzComplete> FEzComplete::FromModel(const Gs2::Mission::Model::FCompletePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzComplete>()
            ->WithMissionGroupName(Model->GetMissionGroupName())
            ->WithCompletedMissionTaskNames(Model->GetCompletedMissionTaskNames())
            ->WithReceivedMissionTaskNames(Model->GetReceivedMissionTaskNames());
    }
}