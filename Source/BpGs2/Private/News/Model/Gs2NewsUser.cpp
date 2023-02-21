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

#include "BpGs2/Public/News/Model/Gs2NewsUser.h"
#include "BpGs2/Public/News/Model/Gs2NewsNews.h"
#include "BpGs2/Public/News/Model/Gs2NewsSetCookieRequestEntry.h"
#include "Core/Model/Gs2AccessToken.h"
#include "News/Model/Gs2NewsNews.h"
#include "News/Model/Gs2NewsSetCookieRequestEntry.h"
#include "Core/BpGs2Constant.h"

FGs2NewsOwnNews UGs2NewsUserFunctionLibrary::OwnNews(
    FGs2NewsOwnUser User
)
{
    FGs2NewsOwnNews Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2NewsUserFunctionLibrary::OwnNews] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->News(
    );
    return Return;
}