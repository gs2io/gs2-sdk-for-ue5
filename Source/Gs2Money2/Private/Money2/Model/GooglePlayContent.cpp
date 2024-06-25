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

#include "Money2/Model/GooglePlayContent.h"

namespace Gs2::Money2::Model
{
    FGooglePlayContent::FGooglePlayContent():
        ProductIdValue(TOptional<FString>())
    {
    }

    FGooglePlayContent::FGooglePlayContent(
        const FGooglePlayContent& From
    ):
        ProductIdValue(From.ProductIdValue)
    {
    }

    TSharedPtr<FGooglePlayContent> FGooglePlayContent::WithProductId(
        const TOptional<FString> ProductId
    )
    {
        this->ProductIdValue = ProductId;
        return SharedThis(this);
    }
    TOptional<FString> FGooglePlayContent::GetProductId() const
    {
        return ProductIdValue;
    }

    TSharedPtr<FGooglePlayContent> FGooglePlayContent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGooglePlayContent>()
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

    TSharedPtr<FJsonObject> FGooglePlayContent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProductIdValue.IsSet())
        {
            JsonRootObject->SetStringField("productId", ProductIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGooglePlayContent::TypeName = "GooglePlayContent";
}