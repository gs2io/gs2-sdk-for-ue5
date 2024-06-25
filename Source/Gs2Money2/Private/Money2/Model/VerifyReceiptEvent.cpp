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

#include "Money2/Model/VerifyReceiptEvent.h"

namespace Gs2::Money2::Model
{
    FVerifyReceiptEvent::FVerifyReceiptEvent():
        ContentNameValue(TOptional<FString>()),
        PlatformValue(TOptional<FString>()),
        AppleAppStoreVerifyReceiptEventValue(nullptr),
        GooglePlayVerifyReceiptEventValue(nullptr)
    {
    }

    FVerifyReceiptEvent::FVerifyReceiptEvent(
        const FVerifyReceiptEvent& From
    ):
        ContentNameValue(From.ContentNameValue),
        PlatformValue(From.PlatformValue),
        AppleAppStoreVerifyReceiptEventValue(From.AppleAppStoreVerifyReceiptEventValue),
        GooglePlayVerifyReceiptEventValue(From.GooglePlayVerifyReceiptEventValue)
    {
    }

    TSharedPtr<FVerifyReceiptEvent> FVerifyReceiptEvent::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReceiptEvent> FVerifyReceiptEvent::WithPlatform(
        const TOptional<FString> Platform
    )
    {
        this->PlatformValue = Platform;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReceiptEvent> FVerifyReceiptEvent::WithAppleAppStoreVerifyReceiptEvent(
        const TSharedPtr<FAppleAppStoreVerifyReceiptEvent> AppleAppStoreVerifyReceiptEvent
    )
    {
        this->AppleAppStoreVerifyReceiptEventValue = AppleAppStoreVerifyReceiptEvent;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReceiptEvent> FVerifyReceiptEvent::WithGooglePlayVerifyReceiptEvent(
        const TSharedPtr<FGooglePlayVerifyReceiptEvent> GooglePlayVerifyReceiptEvent
    )
    {
        this->GooglePlayVerifyReceiptEventValue = GooglePlayVerifyReceiptEvent;
        return SharedThis(this);
    }
    TOptional<FString> FVerifyReceiptEvent::GetContentName() const
    {
        return ContentNameValue;
    }
    TOptional<FString> FVerifyReceiptEvent::GetPlatform() const
    {
        return PlatformValue;
    }
    TSharedPtr<FAppleAppStoreVerifyReceiptEvent> FVerifyReceiptEvent::GetAppleAppStoreVerifyReceiptEvent() const
    {
        return AppleAppStoreVerifyReceiptEventValue;
    }
    TSharedPtr<FGooglePlayVerifyReceiptEvent> FVerifyReceiptEvent::GetGooglePlayVerifyReceiptEvent() const
    {
        return GooglePlayVerifyReceiptEventValue;
    }

    TSharedPtr<FVerifyReceiptEvent> FVerifyReceiptEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyReceiptEvent>()
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
            ->WithAppleAppStoreVerifyReceiptEvent(Data->HasField(ANSI_TO_TCHAR("appleAppStoreVerifyReceiptEvent")) ? [Data]() -> Model::FAppleAppStoreVerifyReceiptEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("appleAppStoreVerifyReceiptEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FAppleAppStoreVerifyReceiptEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("appleAppStoreVerifyReceiptEvent")));
                 }() : nullptr)
            ->WithGooglePlayVerifyReceiptEvent(Data->HasField(ANSI_TO_TCHAR("googlePlayVerifyReceiptEvent")) ? [Data]() -> Model::FGooglePlayVerifyReceiptEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("googlePlayVerifyReceiptEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FGooglePlayVerifyReceiptEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("googlePlayVerifyReceiptEvent")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FVerifyReceiptEvent::ToJson() const
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
        if (AppleAppStoreVerifyReceiptEventValue != nullptr && AppleAppStoreVerifyReceiptEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("appleAppStoreVerifyReceiptEvent", AppleAppStoreVerifyReceiptEventValue->ToJson());
        }
        if (GooglePlayVerifyReceiptEventValue != nullptr && GooglePlayVerifyReceiptEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("googlePlayVerifyReceiptEvent", GooglePlayVerifyReceiptEventValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FVerifyReceiptEvent::TypeName = "VerifyReceiptEvent";
}