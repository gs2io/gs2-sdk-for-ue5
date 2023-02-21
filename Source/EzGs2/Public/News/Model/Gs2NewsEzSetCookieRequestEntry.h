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
#include "News/Model/SetCookieRequestEntry.h"

namespace Gs2::UE5::News::Model
{
	class EZGS2_API FEzSetCookieRequestEntry final : public TSharedFromThis<FEzSetCookieRequestEntry>
	{
        TOptional<FString> KeyValue;
        TOptional<FString> ValueValue;

	public:
        TSharedPtr<FEzSetCookieRequestEntry> WithKey(const TOptional<FString> Key);
        TSharedPtr<FEzSetCookieRequestEntry> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetKey() const;

        TOptional<FString> GetValue() const;

        Gs2::News::Model::FSetCookieRequestEntryPtr ToModel() const;
        static TSharedPtr<FEzSetCookieRequestEntry> FromModel(Gs2::News::Model::FSetCookieRequestEntryPtr Model);
    };
    typedef TSharedPtr<FEzSetCookieRequestEntry> FEzSetCookieRequestEntryPtr;
}