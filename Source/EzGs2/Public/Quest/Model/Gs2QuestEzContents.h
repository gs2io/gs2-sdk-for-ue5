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
#include "Quest/Model/Contents.h"
#include "Gs2QuestEzAcquireAction.h"

namespace Gs2::UE5::Quest::Model
{
	class EZGS2_API FEzContents final : public TSharedFromThis<FEzContents>
	{
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> CompleteAcquireActionsValue;

	public:
        TSharedPtr<FEzContents> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzContents> WithCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> CompleteAcquireActions);

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> GetCompleteAcquireActions() const;

        Gs2::Quest::Model::FContentsPtr ToModel() const;
        static TSharedPtr<FEzContents> FromModel(Gs2::Quest::Model::FContentsPtr Model);
    };
    typedef TSharedPtr<FEzContents> FEzContentsPtr;
}