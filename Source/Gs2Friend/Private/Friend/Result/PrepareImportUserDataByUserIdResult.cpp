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

#include "Friend/Result/PrepareImportUserDataByUserIdResult.h"

namespace Gs2::Friend::Result
{
    FPrepareImportUserDataByUserIdResult::FPrepareImportUserDataByUserIdResult():
        UploadTokenValue(TOptional<FString>()),
        UploadUrlValue(TOptional<FString>())
    {
    }

    FPrepareImportUserDataByUserIdResult::FPrepareImportUserDataByUserIdResult(
        const FPrepareImportUserDataByUserIdResult& From
    ):
        UploadTokenValue(From.UploadTokenValue),
        UploadUrlValue(From.UploadUrlValue)
    {
    }

    TSharedPtr<FPrepareImportUserDataByUserIdResult> FPrepareImportUserDataByUserIdResult::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareImportUserDataByUserIdResult> FPrepareImportUserDataByUserIdResult::WithUploadUrl(
        const TOptional<FString> UploadUrl
    )
    {
        this->UploadUrlValue = UploadUrl;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareImportUserDataByUserIdResult::GetUploadToken() const
    {
        return UploadTokenValue;
    }

    TOptional<FString> FPrepareImportUserDataByUserIdResult::GetUploadUrl() const
    {
        return UploadUrlValue;
    }

    TSharedPtr<FPrepareImportUserDataByUserIdResult> FPrepareImportUserDataByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareImportUserDataByUserIdResult>()
            ->WithUploadToken(Data->HasField("uploadToken") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("uploadToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUploadUrl(Data->HasField("uploadUrl") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("uploadUrl", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareImportUserDataByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UploadTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadToken", UploadTokenValue.GetValue());
        }
        if (UploadUrlValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadUrl", UploadUrlValue.GetValue());
        }
        return JsonRootObject;
    }
}