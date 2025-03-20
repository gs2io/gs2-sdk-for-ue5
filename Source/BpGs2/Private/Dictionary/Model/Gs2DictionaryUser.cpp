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

#include "Dictionary/Model/Gs2DictionaryUser.h"
#include "Dictionary/Domain/EzGs2Dictionary.h"
#include "Dictionary/Model/Gs2DictionaryEntry.h"
#include "Dictionary/Model/Gs2DictionaryLike.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Dictionary/Model/Gs2DictionaryEntry.h"
#include "Dictionary/Model/Gs2DictionaryLike.h"
#include "Core/BpGs2Constant.h"

FGs2DictionaryOwnEntry UGs2DictionaryUserFunctionLibrary::OwnEntry(
    FGs2DictionaryOwnUser User,
    FString EntryModelName
)
{
    FGs2DictionaryOwnEntry Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryUserFunctionLibrary::OwnEntry] User parameter specification is missing."))
        return Return;
    }
    if (EntryModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryUserFunctionLibrary::OwnEntry] EntryModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Entry(
        EntryModelName
    );
    return Return;
}

FGs2DictionaryOwnLike UGs2DictionaryUserFunctionLibrary::OwnLike(
    FGs2DictionaryOwnUser User,
    FString EntryModelName
)
{
    FGs2DictionaryOwnLike Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryUserFunctionLibrary::OwnLike] User parameter specification is missing."))
        return Return;
    }
    if (EntryModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryUserFunctionLibrary::OwnLike] EntryModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Like(
        EntryModelName
    );
    return Return;
}