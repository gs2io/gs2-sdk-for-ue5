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

#include "Version/Result/CheckImportUserDataByUserIdResult.h"

namespace Gs2::Version::Result
{
    FCheckImportUserDataByUserIdResult::FCheckImportUserDataByUserIdResult():
        UrlValue(TOptional<FString>())
    {
    }

    FCheckImportUserDataByUserIdResult::FCheckImportUserDataByUserIdResult(
        const FCheckImportUserDataByUserIdResult& From
    ):
        UrlValue(From.UrlValue)
    {
    }

    TSharedPtr<FCheckImportUserDataByUserIdResult> FCheckImportUserDataByUserIdResult::WithUrl(
        const TOptional<FString> Url
    )
    {
        this->UrlValue = Url;
        return SharedThis(this);
    }

    TOptional<FString> FCheckImportUserDataByUserIdResult::GetUrl() const
    {
        return UrlValue;
    }

    TSharedPtr<FCheckImportUserDataByUserIdResult> FCheckImportUserDataByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCheckImportUserDataByUserIdResult>()
            ->WithUrl(Data->HasField("url") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("url", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCheckImportUserDataByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UrlValue.IsSet())
        {
            JsonRootObject->SetStringField("url", UrlValue.GetValue());
        }
        return JsonRootObject;
    }
}