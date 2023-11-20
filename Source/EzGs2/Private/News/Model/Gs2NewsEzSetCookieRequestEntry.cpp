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

#include "News/Model/Gs2NewsEzSetCookieRequestEntry.h"

namespace Gs2::UE5::News::Model
{

    TSharedPtr<FEzSetCookieRequestEntry> FEzSetCookieRequestEntry::WithKey(
        const TOptional<FString> Key
    )
    {
        this->KeyValue = Key;
        return SharedThis(this);
    }

    TSharedPtr<FEzSetCookieRequestEntry> FEzSetCookieRequestEntry::WithValue(
        const TOptional<FString> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzSetCookieRequestEntry::GetKey() const
    {
        return KeyValue;
    }
    TOptional<FString> FEzSetCookieRequestEntry::GetValue() const
    {
        return ValueValue;
    }

    Gs2::News::Model::FSetCookieRequestEntryPtr FEzSetCookieRequestEntry::ToModel() const
    {
        return MakeShared<Gs2::News::Model::FSetCookieRequestEntry>()
            ->WithKey(KeyValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzSetCookieRequestEntry> FEzSetCookieRequestEntry::FromModel(const Gs2::News::Model::FSetCookieRequestEntryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSetCookieRequestEntry>()
            ->WithKey(Model->GetKey())
            ->WithValue(Model->GetValue());
    }
}