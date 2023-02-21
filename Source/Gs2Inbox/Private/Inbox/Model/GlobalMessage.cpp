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

#include "Inbox/Model/GlobalMessage.h"

namespace Gs2::Inbox::Model
{
    FGlobalMessage::FGlobalMessage():
        GlobalMessageIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReadAcquireActionsValue(nullptr),
        ExpiresTimeSpanValue(nullptr),
        ExpiresAtValue(TOptional<int64>())
    {
    }

    FGlobalMessage::FGlobalMessage(
        const FGlobalMessage& From
    ):
        GlobalMessageIdValue(From.GlobalMessageIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ReadAcquireActionsValue(From.ReadAcquireActionsValue),
        ExpiresTimeSpanValue(From.ExpiresTimeSpanValue),
        ExpiresAtValue(From.ExpiresAtValue)
    {
    }

    TSharedPtr<FGlobalMessage> FGlobalMessage::WithGlobalMessageId(
        const TOptional<FString> GlobalMessageId
    )
    {
        this->GlobalMessageIdValue = GlobalMessageId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessage> FGlobalMessage::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessage> FGlobalMessage::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessage> FGlobalMessage::WithReadAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions
    )
    {
        this->ReadAcquireActionsValue = ReadAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessage> FGlobalMessage::WithExpiresTimeSpan(
        const TSharedPtr<FTimeSpan> ExpiresTimeSpan
    )
    {
        this->ExpiresTimeSpanValue = ExpiresTimeSpan;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessage> FGlobalMessage::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }
    TOptional<FString> FGlobalMessage::GetGlobalMessageId() const
    {
        return GlobalMessageIdValue;
    }
    TOptional<FString> FGlobalMessage::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FGlobalMessage::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FGlobalMessage::GetReadAcquireActions() const
    {
        return ReadAcquireActionsValue;
    }
    TSharedPtr<FTimeSpan> FGlobalMessage::GetExpiresTimeSpan() const
    {
        return ExpiresTimeSpanValue;
    }
    TOptional<int64> FGlobalMessage::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FGlobalMessage::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    TOptional<FString> FGlobalMessage::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalMessage::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalMessage::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalMessage::GetGlobalMessageNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGlobalMessage> FGlobalMessage::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGlobalMessage>()
            ->WithGlobalMessageId(Data->HasField("globalMessageId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("globalMessageId", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
                 }() : nullptr)
            ->WithExpiresTimeSpan(Data->HasField("expiresTimeSpan") ? [Data]() -> Model::FTimeSpanPtr
                {
                    if (Data->HasTypedField<EJson::Null>("expiresTimeSpan"))
                    {
                        return nullptr;
                    }
                    return Model::FTimeSpan::FromJson(Data->GetObjectField("expiresTimeSpan"));
                 }() : nullptr)
            ->WithExpiresAt(Data->HasField("expiresAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("expiresAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FGlobalMessage::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GlobalMessageIdValue.IsSet())
        {
            JsonRootObject->SetStringField("globalMessageId", GlobalMessageIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
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
        if (ExpiresTimeSpanValue != nullptr && ExpiresTimeSpanValue.IsValid())
        {
            JsonRootObject->SetObjectField("expiresTimeSpan", ExpiresTimeSpanValue->ToJson());
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FGlobalMessage::TypeName = "GlobalMessage";
}