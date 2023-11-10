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

#include "News/Result/PrepareUpdateCurrentNewsMasterResult.h"

namespace Gs2::News::Result
{
    FPrepareUpdateCurrentNewsMasterResult::FPrepareUpdateCurrentNewsMasterResult():
        UploadTokenValue(TOptional<FString>()),
        TemplateUploadUrlValue(TOptional<FString>())
    {
    }

    FPrepareUpdateCurrentNewsMasterResult::FPrepareUpdateCurrentNewsMasterResult(
        const FPrepareUpdateCurrentNewsMasterResult& From
    ):
        UploadTokenValue(From.UploadTokenValue),
        TemplateUploadUrlValue(From.TemplateUploadUrlValue)
    {
    }

    TSharedPtr<FPrepareUpdateCurrentNewsMasterResult> FPrepareUpdateCurrentNewsMasterResult::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUpdateCurrentNewsMasterResult> FPrepareUpdateCurrentNewsMasterResult::WithTemplateUploadUrl(
        const TOptional<FString> TemplateUploadUrl
    )
    {
        this->TemplateUploadUrlValue = TemplateUploadUrl;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareUpdateCurrentNewsMasterResult::GetUploadToken() const
    {
        return UploadTokenValue;
    }

    TOptional<FString> FPrepareUpdateCurrentNewsMasterResult::GetTemplateUploadUrl() const
    {
        return TemplateUploadUrlValue;
    }

    TSharedPtr<FPrepareUpdateCurrentNewsMasterResult> FPrepareUpdateCurrentNewsMasterResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareUpdateCurrentNewsMasterResult>()
            ->WithUploadToken(Data->HasField("uploadToken") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("uploadToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTemplateUploadUrl(Data->HasField("templateUploadUrl") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("templateUploadUrl", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareUpdateCurrentNewsMasterResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UploadTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadToken", UploadTokenValue.GetValue());
        }
        if (TemplateUploadUrlValue.IsSet())
        {
            JsonRootObject->SetStringField("templateUploadUrl", TemplateUploadUrlValue.GetValue());
        }
        return JsonRootObject;
    }
}