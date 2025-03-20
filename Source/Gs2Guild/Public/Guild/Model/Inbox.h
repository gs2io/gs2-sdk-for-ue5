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
#include "ReceiveMemberRequest.h"

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FInbox final : public FGs2Object, public TSharedFromThis<FInbox>
    {
        TOptional<FString> InboxIdValue;
        TOptional<FString> GuildNameValue;
        TSharedPtr<TArray<FString>> FromUserIdsValue;
        TSharedPtr<TArray<TSharedPtr<FReceiveMemberRequest>>> ReceiveMemberRequestsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FInbox();
        FInbox(
            const FInbox& From
        );
        virtual ~FInbox() override = default;

        TSharedPtr<FInbox> WithInboxId(const TOptional<FString> InboxId);
        TSharedPtr<FInbox> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FInbox> WithFromUserIds(const TSharedPtr<TArray<FString>> FromUserIds);
        TSharedPtr<FInbox> WithReceiveMemberRequests(const TSharedPtr<TArray<TSharedPtr<FReceiveMemberRequest>>> ReceiveMemberRequests);
        TSharedPtr<FInbox> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FInbox> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FInbox> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetInboxId() const;
        TOptional<FString> GetGuildName() const;
        TSharedPtr<TArray<FString>> GetFromUserIds() const;
        TSharedPtr<TArray<TSharedPtr<FReceiveMemberRequest>>> GetReceiveMemberRequests() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildNameFromGrn(const FString Grn);

        static TSharedPtr<FInbox> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FInbox, ESPMode::ThreadSafe> FInboxPtr;
}