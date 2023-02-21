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
#include "Dictionary/Model/Entry.h"

namespace Gs2::UE5::Dictionary::Model
{
	class EZGS2_API FEzEntry final : public TSharedFromThis<FEzEntry>
	{
        TOptional<FString> EntryIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TOptional<int64> AcquiredAtValue;

	public:
        TSharedPtr<FEzEntry> WithEntryId(const TOptional<FString> EntryId);
        TSharedPtr<FEzEntry> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzEntry> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzEntry> WithAcquiredAt(const TOptional<int64> AcquiredAt);

        TOptional<FString> GetEntryId() const;

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetName() const;

        TOptional<int64> GetAcquiredAt() const;
        FString GetAcquiredAtString() const;

        Gs2::Dictionary::Model::FEntryPtr ToModel() const;
        static TSharedPtr<FEzEntry> FromModel(Gs2::Dictionary::Model::FEntryPtr Model);
    };
    typedef TSharedPtr<FEzEntry> FEzEntryPtr;
}