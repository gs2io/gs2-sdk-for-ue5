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

#include "EzGs2/Public/Inbox/Model/Gs2InboxEzMessage.h"

namespace Gs2::UE5::Inbox::Model
{

    TSharedPtr<FEzMessage> FEzMessage::WithMessageId(
        const TOptional<FString> MessageId
    )
    {
        this->MessageIdValue = MessageId;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithIsRead(
        const TOptional<bool> IsRead
    )
    {
        this->IsReadValue = IsRead;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithReadAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inbox::Model::FEzAcquireAction>>> ReadAcquireActions
    )
    {
        this->ReadAcquireActionsValue = ReadAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithReceivedAt(
        const TOptional<int64> ReceivedAt
    )
    {
        this->ReceivedAtValue = ReceivedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithReadAt(
        const TOptional<int64> ReadAt
    )
    {
        this->ReadAtValue = ReadAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzMessage> FEzMessage::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzMessage::GetMessageId() const
    {
        return MessageIdValue;
    }
    TOptional<FString> FEzMessage::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzMessage::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<bool> FEzMessage::GetIsRead() const
    {
        return IsReadValue;
    }

    FString FEzMessage::GetIsReadString() const
    {
        if (!IsReadValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsReadValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inbox::Model::FEzAcquireAction>>> FEzMessage::GetReadAcquireActions() const
    {
        return ReadAcquireActionsValue;
    }
    TOptional<int64> FEzMessage::GetReceivedAt() const
    {
        return ReceivedAtValue;
    }

    FString FEzMessage::GetReceivedAtString() const
    {
        if (!ReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue());
    }
    TOptional<int64> FEzMessage::GetReadAt() const
    {
        return ReadAtValue;
    }

    FString FEzMessage::GetReadAtString() const
    {
        if (!ReadAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReadAtValue.GetValue());
    }
    TOptional<int64> FEzMessage::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FEzMessage::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    Gs2::Inbox::Model::FMessagePtr FEzMessage::ToModel() const
    {
        return MakeShared<Gs2::Inbox::Model::FMessage>()
            ->WithMessageId(MessageIdValue)
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithIsRead(IsReadValue)
            ->WithReadAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Inbox::Model::FAcquireAction>>>();
                    if (ReadAcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ReadAcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithReceivedAt(ReceivedAtValue)
            ->WithReadAt(ReadAtValue)
            ->WithExpiresAt(ExpiresAtValue);
    }

    TSharedPtr<FEzMessage> FEzMessage::FromModel(const Gs2::Inbox::Model::FMessagePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMessage>()
            ->WithMessageId(Model->GetMessageId())
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithIsRead(Model->GetIsRead())
            ->WithReadAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetReadAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetReadAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithReceivedAt(Model->GetReceivedAt())
            ->WithReadAt(Model->GetReadAt())
            ->WithExpiresAt(Model->GetExpiresAt());
    }
}