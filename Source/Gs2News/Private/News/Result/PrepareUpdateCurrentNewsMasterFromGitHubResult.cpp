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

#include "News/Result/PrepareUpdateCurrentNewsMasterFromGitHubResult.h"

namespace Gs2::News::Result
{
    FPrepareUpdateCurrentNewsMasterFromGitHubResult::FPrepareUpdateCurrentNewsMasterFromGitHubResult():
        UploadTokenValue(TOptional<FString>())
    {
    }

    FPrepareUpdateCurrentNewsMasterFromGitHubResult::FPrepareUpdateCurrentNewsMasterFromGitHubResult(
        const FPrepareUpdateCurrentNewsMasterFromGitHubResult& From
    ):
        UploadTokenValue(From.UploadTokenValue)
    {
    }

    TSharedPtr<FPrepareUpdateCurrentNewsMasterFromGitHubResult> FPrepareUpdateCurrentNewsMasterFromGitHubResult::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareUpdateCurrentNewsMasterFromGitHubResult::GetUploadToken() const
    {
        return UploadTokenValue;
    }

    TSharedPtr<FPrepareUpdateCurrentNewsMasterFromGitHubResult> FPrepareUpdateCurrentNewsMasterFromGitHubResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareUpdateCurrentNewsMasterFromGitHubResult>()
            ->WithUploadToken(Data->HasField("uploadToken") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("uploadToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareUpdateCurrentNewsMasterFromGitHubResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UploadTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadToken", UploadTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}