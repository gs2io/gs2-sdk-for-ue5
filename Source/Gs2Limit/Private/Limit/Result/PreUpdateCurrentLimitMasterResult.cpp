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

#include "Limit/Result/PreUpdateCurrentLimitMasterResult.h"

namespace Gs2::Limit::Result
{
    FPreUpdateCurrentLimitMasterResult::FPreUpdateCurrentLimitMasterResult():
        UploadTokenValue(TOptional<FString>()),
        UploadUrlValue(TOptional<FString>())
    {
    }

    FPreUpdateCurrentLimitMasterResult::FPreUpdateCurrentLimitMasterResult(
        const FPreUpdateCurrentLimitMasterResult& From
    ):
        UploadTokenValue(From.UploadTokenValue),
        UploadUrlValue(From.UploadUrlValue)
    {
    }

    TSharedPtr<FPreUpdateCurrentLimitMasterResult> FPreUpdateCurrentLimitMasterResult::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TSharedPtr<FPreUpdateCurrentLimitMasterResult> FPreUpdateCurrentLimitMasterResult::WithUploadUrl(
        const TOptional<FString> UploadUrl
    )
    {
        this->UploadUrlValue = UploadUrl;
        return SharedThis(this);
    }

    TOptional<FString> FPreUpdateCurrentLimitMasterResult::GetUploadToken() const
    {
        return UploadTokenValue;
    }

    TOptional<FString> FPreUpdateCurrentLimitMasterResult::GetUploadUrl() const
    {
        return UploadUrlValue;
    }

    TSharedPtr<FPreUpdateCurrentLimitMasterResult> FPreUpdateCurrentLimitMasterResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPreUpdateCurrentLimitMasterResult>()
            ->WithUploadToken(Data->HasField(ANSI_TO_TCHAR("uploadToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("uploadToken"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUploadUrl(Data->HasField(ANSI_TO_TCHAR("uploadUrl")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("uploadUrl"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPreUpdateCurrentLimitMasterResult::ToJson() const
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