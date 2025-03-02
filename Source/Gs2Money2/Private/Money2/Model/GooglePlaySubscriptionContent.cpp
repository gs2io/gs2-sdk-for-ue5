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

#include "Money2/Model/GooglePlaySubscriptionContent.h"

namespace Gs2::Money2::Model
{
    FGooglePlaySubscriptionContent::FGooglePlaySubscriptionContent():
        ProductIdValue(TOptional<FString>())
    {
    }

    FGooglePlaySubscriptionContent::FGooglePlaySubscriptionContent(
        const FGooglePlaySubscriptionContent& From
    ):
        ProductIdValue(From.ProductIdValue)
    {
    }

    TSharedPtr<FGooglePlaySubscriptionContent> FGooglePlaySubscriptionContent::WithProductId(
        const TOptional<FString> ProductId
    )
    {
        this->ProductIdValue = ProductId;
        return SharedThis(this);
    }
    TOptional<FString> FGooglePlaySubscriptionContent::GetProductId() const
    {
        return ProductIdValue;
    }

    TSharedPtr<FGooglePlaySubscriptionContent> FGooglePlaySubscriptionContent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGooglePlaySubscriptionContent>()
            ->WithProductId(Data->HasField(ANSI_TO_TCHAR("productId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("productId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGooglePlaySubscriptionContent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProductIdValue.IsSet())
        {
            JsonRootObject->SetStringField("productId", ProductIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGooglePlaySubscriptionContent::TypeName = "GooglePlaySubscriptionContent";
}