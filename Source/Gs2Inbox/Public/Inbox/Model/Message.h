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
#include "AcquireAction.h"

namespace Gs2::Inbox::Model
{
    class GS2INBOX_API FMessage final : public Gs2Object, public TSharedFromThis<FMessage>
    {
        TOptional<FString> MessageIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MetadataValue;
        TOptional<bool> IsReadValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> ReadAcquireActionsValue;
        TOptional<int64> ReceivedAtValue;
        TOptional<int64> ReadAtValue;
        TOptional<int64> ExpiresAtValue;

    public:
        FMessage();
        FMessage(
            const FMessage& From
        );
        virtual ~FMessage() override = default;

        TSharedPtr<FMessage> WithMessageId(const TOptional<FString> MessageId);
        TSharedPtr<FMessage> WithName(const TOptional<FString> Name);
        TSharedPtr<FMessage> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMessage> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMessage> WithIsRead(const TOptional<bool> IsRead);
        TSharedPtr<FMessage> WithReadAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> ReadAcquireActions);
        TSharedPtr<FMessage> WithReceivedAt(const TOptional<int64> ReceivedAt);
        TSharedPtr<FMessage> WithReadAt(const TOptional<int64> ReadAt);
        TSharedPtr<FMessage> WithExpiresAt(const TOptional<int64> ExpiresAt);

        TOptional<FString> GetMessageId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMetadata() const;
        TOptional<bool> GetIsRead() const;
        FString GetIsReadString() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetReadAcquireActions() const;
        TOptional<int64> GetReceivedAt() const;
        FString GetReceivedAtString() const;
        TOptional<int64> GetReadAt() const;
        FString GetReadAtString() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetMessageNameFromGrn(const FString Grn);

        static TSharedPtr<FMessage> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMessage, ESPMode::ThreadSafe> FMessagePtr;
}