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

#include "Money2/Model/AppleAppStoreSetting.h"

namespace Gs2::Money2::Model
{
    FAppleAppStoreSetting::FAppleAppStoreSetting():
        BundleIdValue(TOptional<FString>())
    {
    }

    FAppleAppStoreSetting::FAppleAppStoreSetting(
        const FAppleAppStoreSetting& From
    ):
        BundleIdValue(From.BundleIdValue)
    {
    }

    TSharedPtr<FAppleAppStoreSetting> FAppleAppStoreSetting::WithBundleId(
        const TOptional<FString> BundleId
    )
    {
        this->BundleIdValue = BundleId;
        return SharedThis(this);
    }
    TOptional<FString> FAppleAppStoreSetting::GetBundleId() const
    {
        return BundleIdValue;
    }

    TSharedPtr<FAppleAppStoreSetting> FAppleAppStoreSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAppleAppStoreSetting>()
            ->WithBundleId(Data->HasField(ANSI_TO_TCHAR("bundleId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("bundleId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAppleAppStoreSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BundleIdValue.IsSet())
        {
            JsonRootObject->SetStringField("bundleId", BundleIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAppleAppStoreSetting::TypeName = "AppleAppStoreSetting";
}