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
#include "Inbox/Model/Message.h"
#include "Gs2InboxEzAcquireAction.h"

namespace Gs2::UE5::Inbox::Model
{
	class EZGS2_API FEzMessage final : public TSharedFromThis<FEzMessage>
	{
        TOptional<FString> MessageIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<bool> IsReadValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inbox::Model::FEzAcquireAction>>> ReadAcquireActionsValue;
        TOptional<int64> ReceivedAtValue;
        TOptional<int64> ReadAtValue;
        TOptional<int64> ExpiresAtValue;

	public:
        TSharedPtr<FEzMessage> WithMessageId(const TOptional<FString> MessageId);
        TSharedPtr<FEzMessage> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzMessage> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzMessage> WithIsRead(const TOptional<bool> IsRead);
        TSharedPtr<FEzMessage> WithReadAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inbox::Model::FEzAcquireAction>>> ReadAcquireActions);
        TSharedPtr<FEzMessage> WithReceivedAt(const TOptional<int64> ReceivedAt);
        TSharedPtr<FEzMessage> WithReadAt(const TOptional<int64> ReadAt);
        TSharedPtr<FEzMessage> WithExpiresAt(const TOptional<int64> ExpiresAt);

        TOptional<FString> GetMessageId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<bool> GetIsRead() const;
        FString GetIsReadString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inbox::Model::FEzAcquireAction>>> GetReadAcquireActions() const;

        TOptional<int64> GetReceivedAt() const;
        FString GetReceivedAtString() const;

        TOptional<int64> GetReadAt() const;
        FString GetReadAtString() const;

        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        Gs2::Inbox::Model::FMessagePtr ToModel() const;
        static TSharedPtr<FEzMessage> FromModel(Gs2::Inbox::Model::FMessagePtr Model);
    };
    typedef TSharedPtr<FEzMessage> FEzMessagePtr;
}