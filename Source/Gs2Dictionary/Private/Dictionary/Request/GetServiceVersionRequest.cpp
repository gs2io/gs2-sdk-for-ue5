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

#include "Dictionary/Request/GetServiceVersionRequest.h"

namespace Gs2::Dictionary::Request
{
    FGetServiceVersionRequest::FGetServiceVersionRequest()
    {
    }

    FGetServiceVersionRequest::FGetServiceVersionRequest(
        const FGetServiceVersionRequest& From
    )
    {
    }

    TSharedPtr<FGetServiceVersionRequest> FGetServiceVersionRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TOptional<FString> FGetServiceVersionRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TSharedPtr<FGetServiceVersionRequest> FGetServiceVersionRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetServiceVersionRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetServiceVersionRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        return JsonRootObject;
    }
}