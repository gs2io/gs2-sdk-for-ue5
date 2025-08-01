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

#include "Deploy/Request/PreCreateStackRequest.h"

namespace Gs2::Deploy::Request
{
    FPreCreateStackRequest::FPreCreateStackRequest()
    {
    }

    FPreCreateStackRequest::FPreCreateStackRequest(
        const FPreCreateStackRequest& From
    )
    {
    }

    TSharedPtr<FPreCreateStackRequest> FPreCreateStackRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TOptional<FString> FPreCreateStackRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TSharedPtr<FPreCreateStackRequest> FPreCreateStackRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPreCreateStackRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPreCreateStackRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        return JsonRootObject;
    }
}