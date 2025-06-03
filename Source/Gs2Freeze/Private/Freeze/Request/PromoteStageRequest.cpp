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

#include "Freeze/Request/PromoteStageRequest.h"

namespace Gs2::Freeze::Request
{
    FPromoteStageRequest::FPromoteStageRequest():
        StageNameValue(TOptional<FString>())
    {
    }

    FPromoteStageRequest::FPromoteStageRequest(
        const FPromoteStageRequest& From
    ):
        StageNameValue(From.StageNameValue)
    {
    }

    TSharedPtr<FPromoteStageRequest> FPromoteStageRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPromoteStageRequest> FPromoteStageRequest::WithStageName(
        const TOptional<FString> StageName
    )
    {
        this->StageNameValue = StageName;
        return SharedThis(this);
    }

    TOptional<FString> FPromoteStageRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPromoteStageRequest::GetStageName() const
    {
        return StageNameValue;
    }

    TSharedPtr<FPromoteStageRequest> FPromoteStageRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPromoteStageRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithStageName(Data->HasField(ANSI_TO_TCHAR("stageName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stageName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPromoteStageRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (StageNameValue.IsSet())
        {
            JsonRootObject->SetStringField("stageName", StageNameValue.GetValue());
        }
        return JsonRootObject;
    }
}