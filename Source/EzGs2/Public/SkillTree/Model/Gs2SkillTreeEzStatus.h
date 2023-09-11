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
#include "SkillTree/Model/Status.h"

namespace Gs2::UE5::SkillTree::Model
{
	class EZGS2_API FEzStatus final : public TSharedFromThis<FEzStatus>
	{
        TOptional<FString> StatusIdValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> ReleasedNodeNamesValue;

	public:
        TSharedPtr<FEzStatus> WithStatusId(const TOptional<FString> StatusId);
        TSharedPtr<FEzStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzStatus> WithReleasedNodeNames(const TSharedPtr<TArray<FString>> ReleasedNodeNames);

        TOptional<FString> GetStatusId() const;

        TOptional<FString> GetUserId() const;

        TSharedPtr<TArray<FString>> GetReleasedNodeNames() const;

        Gs2::SkillTree::Model::FStatusPtr ToModel() const;
        static TSharedPtr<FEzStatus> FromModel(Gs2::SkillTree::Model::FStatusPtr Model);
    };
    typedef TSharedPtr<FEzStatus> FEzStatusPtr;
}