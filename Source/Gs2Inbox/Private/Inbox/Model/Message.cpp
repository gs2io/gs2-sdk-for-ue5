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

#include "Inbox/Model/Message.h"

namespace Gs2::Inbox::Model
{
    FMessage::FMessage():
        MessageIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        IsReadValue(TOptional<bool>()),
        ReadAcquireActionsValue(nullptr),
        ReceivedAtValue(TOptional<int64>()),
        ReadAtValue(TOptional<int64>()),
        ExpiresAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FMessage::FMessage(
        const FMessage& From
    ):
        MessageIdValue(From.MessageIdValue),
        NameValue(From.NameValue),
        UserIdValue(From.UserIdValue),
        MetadataValue(From.MetadataValue),
        IsReadValue(From.IsReadValue),
        ReadAcquireActionsValue(From.ReadAcquireActionsValue),
        ReceivedAtValue(From.ReceivedAtValue),
        ReadAtValue(From.ReadAtValue),
        ExpiresAtValue(From.ExpiresAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FMessage> FMessage::WithMessageId(
        const TOptional<FString> MessageId
    )
    {
        this->MessageIdValue = MessageId;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithIsRead(
        const TOptional<bool> IsRead
    )
    {
        this->IsReadValue = IsRead;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithReadAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions
    )
    {
        this->ReadAcquireActionsValue = ReadAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithReceivedAt(
        const TOptional<int64> ReceivedAt
    )
    {
        this->ReceivedAtValue = ReceivedAt;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithReadAt(
        const TOptional<int64> ReadAt
    )
    {
        this->ReadAtValue = ReadAt;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FMessage> FMessage::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FMessage::GetMessageId() const
    {
        return MessageIdValue;
    }
    TOptional<FString> FMessage::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMessage::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FMessage::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<bool> FMessage::GetIsRead() const
    {
        return IsReadValue;
    }

    FString FMessage::GetIsReadString() const
    {
        if (!IsReadValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsReadValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FMessage::GetReadAcquireActions() const
    {
        return ReadAcquireActionsValue;
    }
    TOptional<int64> FMessage::GetReceivedAt() const
    {
        return ReceivedAtValue;
    }

    FString FMessage::GetReceivedAtString() const
    {
        if (!ReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue());
    }
    TOptional<int64> FMessage::GetReadAt() const
    {
        return ReadAtValue;
    }

    FString FMessage::GetReadAtString() const
    {
        if (!ReadAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReadAtValue.GetValue());
    }
    TOptional<int64> FMessage::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FMessage::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }
    TOptional<int64> FMessage::GetRevision() const
    {
        return RevisionValue;
    }

    FString FMessage::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FMessage::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):user:(?<userId>.+):message:(?<messageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMessage::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):user:(?<userId>.+):message:(?<messageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMessage::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):user:(?<userId>.+):message:(?<messageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMessage::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):user:(?<userId>.+):message:(?<messageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMessage::GetMessageNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):user:(?<userId>.+):message:(?<messageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FMessage> FMessage::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMessage>()
            ->WithMessageId(Data->HasField("messageId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("messageId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIsRead(Data->HasField("isRead") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("isRead", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithReadAcquireActions(Data->HasField("readAcquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("readAcquireActions") && Data->HasTypedField<EJson::Array>("readAcquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("readAcquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithReceivedAt(Data->HasField("receivedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("receivedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithReadAt(Data->HasField("readAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("readAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithExpiresAt(Data->HasField("expiresAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("expiresAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FMessage::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MessageIdValue.IsSet())
        {
            JsonRootObject->SetStringField("messageId", MessageIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (IsReadValue.IsSet())
        {
            JsonRootObject->SetBoolField("isRead", IsReadValue.GetValue());
        }
        if (ReadAcquireActionsValue != nullptr && ReadAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReadAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("readAcquireActions", v);
        }
        if (ReceivedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("receivedAt", FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue()));
        }
        if (ReadAtValue.IsSet())
        {
            JsonRootObject->SetStringField("readAt", FString::Printf(TEXT("%lld"), ReadAtValue.GetValue()));
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FMessage::TypeName = "Message";
}