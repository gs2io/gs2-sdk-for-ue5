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

#include "Money2/Model/AppleAppStoreSubscriptionContent.h"

namespace Gs2::Money2::Model
{
    FAppleAppStoreSubscriptionContent::FAppleAppStoreSubscriptionContent():
        SubscriptionGroupIdentifierValue(TOptional<FString>())
    {
    }

    FAppleAppStoreSubscriptionContent::FAppleAppStoreSubscriptionContent(
        const FAppleAppStoreSubscriptionContent& From
    ):
        SubscriptionGroupIdentifierValue(From.SubscriptionGroupIdentifierValue)
    {
    }

    TSharedPtr<FAppleAppStoreSubscriptionContent> FAppleAppStoreSubscriptionContent::WithSubscriptionGroupIdentifier(
        const TOptional<FString> SubscriptionGroupIdentifier
    )
    {
        this->SubscriptionGroupIdentifierValue = SubscriptionGroupIdentifier;
        return SharedThis(this);
    }
    TOptional<FString> FAppleAppStoreSubscriptionContent::GetSubscriptionGroupIdentifier() const
    {
        return SubscriptionGroupIdentifierValue;
    }

    TSharedPtr<FAppleAppStoreSubscriptionContent> FAppleAppStoreSubscriptionContent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAppleAppStoreSubscriptionContent>()
            ->WithSubscriptionGroupIdentifier(Data->HasField(ANSI_TO_TCHAR("subscriptionGroupIdentifier")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subscriptionGroupIdentifier"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAppleAppStoreSubscriptionContent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SubscriptionGroupIdentifierValue.IsSet())
        {
            JsonRootObject->SetStringField("subscriptionGroupIdentifier", SubscriptionGroupIdentifierValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAppleAppStoreSubscriptionContent::TypeName = "AppleAppStoreSubscriptionContent";
}