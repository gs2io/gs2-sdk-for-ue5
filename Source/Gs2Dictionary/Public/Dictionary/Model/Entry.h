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

namespace Gs2::Dictionary::Model
{
    class GS2DICTIONARY_API FEntry final : public TSharedFromThis<FEntry>
    {
        TOptional<FString> EntryIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TOptional<int64> AcquiredAtValue;

    public:
        FEntry();
        FEntry(
            const FEntry& From
        );
        ~FEntry() = default;

        TSharedPtr<FEntry> WithEntryId(const TOptional<FString> EntryId);
        TSharedPtr<FEntry> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEntry> WithName(const TOptional<FString> Name);
        TSharedPtr<FEntry> WithAcquiredAt(const TOptional<int64> AcquiredAt);

        TOptional<FString> GetEntryId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;
        TOptional<int64> GetAcquiredAt() const;
        FString GetAcquiredAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetEntryModelNameFromGrn(const FString Grn);

        static TSharedPtr<FEntry> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEntry, ESPMode::ThreadSafe> FEntryPtr;
}