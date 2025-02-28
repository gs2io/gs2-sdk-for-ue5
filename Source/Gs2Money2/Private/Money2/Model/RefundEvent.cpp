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

#include "Money2/Model/RefundEvent.h"

namespace Gs2::Money2::Model
{
    FRefundEvent::FRefundEvent():
        ContentNameValue(TOptional<FString>()),
        PlatformValue(TOptional<FString>()),
        AppleAppStoreRefundEventValue(nullptr),
        GooglePlayRefundEventValue(nullptr)
    {
    }

    FRefundEvent::FRefundEvent(
        const FRefundEvent& From
    ):
        ContentNameValue(From.ContentNameValue),
        PlatformValue(From.PlatformValue),
        AppleAppStoreRefundEventValue(From.AppleAppStoreRefundEventValue),
        GooglePlayRefundEventValue(From.GooglePlayRefundEventValue)
    {
    }

    TSharedPtr<FRefundEvent> FRefundEvent::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TSharedPtr<FRefundEvent> FRefundEvent::WithPlatform(
        const TOptional<FString> Platform
    )
    {
        this->PlatformValue = Platform;
        return SharedThis(this);
    }

    TSharedPtr<FRefundEvent> FRefundEvent::WithAppleAppStoreRefundEvent(
        const TSharedPtr<FAppleAppStoreVerifyReceiptEvent> AppleAppStoreRefundEvent
    )
    {
        this->AppleAppStoreRefundEventValue = AppleAppStoreRefundEvent;
        return SharedThis(this);
    }

    TSharedPtr<FRefundEvent> FRefundEvent::WithGooglePlayRefundEvent(
        const TSharedPtr<FGooglePlayVerifyReceiptEvent> GooglePlayRefundEvent
    )
    {
        this->GooglePlayRefundEventValue = GooglePlayRefundEvent;
        return SharedThis(this);
    }
    TOptional<FString> FRefundEvent::GetContentName() const
    {
        return ContentNameValue;
    }
    TOptional<FString> FRefundEvent::GetPlatform() const
    {
        return PlatformValue;
    }
    TSharedPtr<FAppleAppStoreVerifyReceiptEvent> FRefundEvent::GetAppleAppStoreRefundEvent() const
    {
        return AppleAppStoreRefundEventValue;
    }
    TSharedPtr<FGooglePlayVerifyReceiptEvent> FRefundEvent::GetGooglePlayRefundEvent() const
    {
        return GooglePlayRefundEventValue;
    }

    TSharedPtr<FRefundEvent> FRefundEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRefundEvent>()
            ->WithContentName(Data->HasField(ANSI_TO_TCHAR("contentName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contentName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPlatform(Data->HasField(ANSI_TO_TCHAR("platform")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("platform"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAppleAppStoreRefundEvent(Data->HasField(ANSI_TO_TCHAR("appleAppStoreRefundEvent")) ? [Data]() -> Model::FAppleAppStoreVerifyReceiptEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("appleAppStoreRefundEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FAppleAppStoreVerifyReceiptEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("appleAppStoreRefundEvent")));
                 }() : nullptr)
            ->WithGooglePlayRefundEvent(Data->HasField(ANSI_TO_TCHAR("googlePlayRefundEvent")) ? [Data]() -> Model::FGooglePlayVerifyReceiptEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("googlePlayRefundEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FGooglePlayVerifyReceiptEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("googlePlayRefundEvent")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FRefundEvent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContentNameValue.IsSet())
        {
            JsonRootObject->SetStringField("contentName", ContentNameValue.GetValue());
        }
        if (PlatformValue.IsSet())
        {
            JsonRootObject->SetStringField("platform", PlatformValue.GetValue());
        }
        if (AppleAppStoreRefundEventValue != nullptr && AppleAppStoreRefundEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("appleAppStoreRefundEvent", AppleAppStoreRefundEventValue->ToJson());
        }
        if (GooglePlayRefundEventValue != nullptr && GooglePlayRefundEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("googlePlayRefundEvent", GooglePlayRefundEventValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FRefundEvent::TypeName = "RefundEvent";
}