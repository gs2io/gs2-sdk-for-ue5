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

#include "Lottery/Result/PreUpdateCurrentLotteryMasterResult.h"

namespace Gs2::Lottery::Result
{
    FPreUpdateCurrentLotteryMasterResult::FPreUpdateCurrentLotteryMasterResult():
        UploadTokenValue(TOptional<FString>()),
        UploadUrlValue(TOptional<FString>())
    {
    }

    FPreUpdateCurrentLotteryMasterResult::FPreUpdateCurrentLotteryMasterResult(
        const FPreUpdateCurrentLotteryMasterResult& From
    ):
        UploadTokenValue(From.UploadTokenValue),
        UploadUrlValue(From.UploadUrlValue)
    {
    }

    TSharedPtr<FPreUpdateCurrentLotteryMasterResult> FPreUpdateCurrentLotteryMasterResult::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TSharedPtr<FPreUpdateCurrentLotteryMasterResult> FPreUpdateCurrentLotteryMasterResult::WithUploadUrl(
        const TOptional<FString> UploadUrl
    )
    {
        this->UploadUrlValue = UploadUrl;
        return SharedThis(this);
    }

    TOptional<FString> FPreUpdateCurrentLotteryMasterResult::GetUploadToken() const
    {
        return UploadTokenValue;
    }

    TOptional<FString> FPreUpdateCurrentLotteryMasterResult::GetUploadUrl() const
    {
        return UploadUrlValue;
    }

    TSharedPtr<FPreUpdateCurrentLotteryMasterResult> FPreUpdateCurrentLotteryMasterResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPreUpdateCurrentLotteryMasterResult>()
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

    TSharedPtr<FJsonObject> FPreUpdateCurrentLotteryMasterResult::ToJson() const
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