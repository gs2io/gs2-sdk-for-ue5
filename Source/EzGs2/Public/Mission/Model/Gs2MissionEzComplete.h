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
#include "Mission/Model/Complete.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzComplete final : public TSharedFromThis<FEzComplete>
	{
        TOptional<FString> MissionGroupNameValue;
        TSharedPtr<TArray<FString>> CompletedMissionTaskNamesValue;
        TSharedPtr<TArray<FString>> ReceivedMissionTaskNamesValue;

	public:
        TSharedPtr<FEzComplete> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FEzComplete> WithCompletedMissionTaskNames(const TSharedPtr<TArray<FString>> CompletedMissionTaskNames);
        TSharedPtr<FEzComplete> WithReceivedMissionTaskNames(const TSharedPtr<TArray<FString>> ReceivedMissionTaskNames);

        TOptional<FString> GetMissionGroupName() const;

        TSharedPtr<TArray<FString>> GetCompletedMissionTaskNames() const;

        TSharedPtr<TArray<FString>> GetReceivedMissionTaskNames() const;

        Gs2::Mission::Model::FCompletePtr ToModel() const;
        static TSharedPtr<FEzComplete> FromModel(Gs2::Mission::Model::FCompletePtr Model);
    };
    typedef TSharedPtr<FEzComplete> FEzCompletePtr;
}