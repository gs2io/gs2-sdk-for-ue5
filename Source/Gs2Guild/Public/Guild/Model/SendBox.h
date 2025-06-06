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
#include "Core/Gs2Object.h"

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FSendBox final : public FGs2Object, public TSharedFromThis<FSendBox>
    {
        TOptional<FString> SendBoxIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GuildModelNameValue;
        TSharedPtr<TArray<FString>> TargetGuildNamesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSendBox();
        FSendBox(
            const FSendBox& From
        );
        virtual ~FSendBox() override = default;

        TSharedPtr<FSendBox> WithSendBoxId(const TOptional<FString> SendBoxId);
        TSharedPtr<FSendBox> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendBox> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FSendBox> WithTargetGuildNames(const TSharedPtr<TArray<FString>> TargetGuildNames);
        TSharedPtr<FSendBox> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSendBox> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSendBox> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSendBoxId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGuildModelName() const;
        TSharedPtr<TArray<FString>> GetTargetGuildNames() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetGuildModelNameFromGrn(const FString Grn);

        static TSharedPtr<FSendBox> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSendBox, ESPMode::ThreadSafe> FSendBoxPtr;
}