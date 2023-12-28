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

#include "Inventory/Request/AcquireItemSetWithGradeByStampSheetRequest.h"

namespace Gs2::Inventory::Request
{
    FAcquireItemSetWithGradeByStampSheetRequest::FAcquireItemSetWithGradeByStampSheetRequest():
        StampSheetValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FAcquireItemSetWithGradeByStampSheetRequest::FAcquireItemSetWithGradeByStampSheetRequest(
        const FAcquireItemSetWithGradeByStampSheetRequest& From
    ):
        StampSheetValue(From.StampSheetValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetRequest> FAcquireItemSetWithGradeByStampSheetRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetRequest> FAcquireItemSetWithGradeByStampSheetRequest::WithStampSheet(
        const TOptional<FString> StampSheet
    )
    {
        this->StampSheetValue = StampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetRequest> FAcquireItemSetWithGradeByStampSheetRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FAcquireItemSetWithGradeByStampSheetRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FAcquireItemSetWithGradeByStampSheetRequest::GetStampSheet() const
    {
        return StampSheetValue;
    }

    TOptional<FString> FAcquireItemSetWithGradeByStampSheetRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetRequest> FAcquireItemSetWithGradeByStampSheetRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireItemSetWithGradeByStampSheetRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithStampSheet(Data->HasField("stampSheet") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("stampSheet", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAcquireItemSetWithGradeByStampSheetRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (StampSheetValue.IsSet())
        {
            JsonRootObject->SetStringField("stampSheet", StampSheetValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}