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

#include "Dictionary/Model/Gs2DictionaryEzEntry.h"

namespace Gs2::UE5::Dictionary::Model
{

    TSharedPtr<FEzEntry> FEzEntry::WithEntryId(
        const TOptional<FString> EntryId
    )
    {
        this->EntryIdValue = EntryId;
        return SharedThis(this);
    }

    TSharedPtr<FEzEntry> FEzEntry::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzEntry> FEzEntry::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzEntry> FEzEntry::WithAcquiredAt(
        const TOptional<int64> AcquiredAt
    )
    {
        this->AcquiredAtValue = AcquiredAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzEntry::GetEntryId() const
    {
        return EntryIdValue;
    }
    TOptional<FString> FEzEntry::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzEntry::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FEzEntry::GetAcquiredAt() const
    {
        return AcquiredAtValue;
    }

    FString FEzEntry::GetAcquiredAtString() const
    {
        if (!AcquiredAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AcquiredAtValue.GetValue());
    }

    Gs2::Dictionary::Model::FEntryPtr FEzEntry::ToModel() const
    {
        return MakeShared<Gs2::Dictionary::Model::FEntry>()
            ->WithEntryId(EntryIdValue)
            ->WithUserId(UserIdValue)
            ->WithName(NameValue)
            ->WithAcquiredAt(AcquiredAtValue);
    }

    TSharedPtr<FEzEntry> FEzEntry::FromModel(const Gs2::Dictionary::Model::FEntryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzEntry>()
            ->WithEntryId(Model->GetEntryId())
            ->WithUserId(Model->GetUserId())
            ->WithName(Model->GetName())
            ->WithAcquiredAt(Model->GetAcquiredAt());
    }
}