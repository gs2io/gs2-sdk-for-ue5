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

#include "Util/Gs2AccountAuthenticator.h"

#include "Account/Gs2AccountRestClient.h"
#include "Auth/Gs2AuthRestClient.h"

namespace Gs2::UE5::Util
{
    FGs2AccountAuthenticator::FGs2AccountAuthenticator(
        const FString AccountNamespaceName,
        const FString KeyId
    ):
        AccountNamespaceName(AccountNamespaceName),
        KeyId(KeyId)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2AccountAuthenticator::Authentication(
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
        const FString UserId,
        const FString Password,
        const TSharedPtr<Gs2::UE5::Auth::Model::FEzAccessTokenPtr> Result
    )
    {
        const auto AccountClient = MakeShared<Gs2::Account::FGs2AccountRestClient>(RestSession);
        const auto AuthClient = MakeShared<Gs2::Auth::FGs2AuthRestClient>(RestSession);
        Account::Result::FAuthenticationResultPtr AuthenticationResult;
        {
            const auto Future = AccountClient->Authentication(
                MakeShared<Gs2::Account::Request::FAuthenticationRequest>()
                    ->WithNamespaceName(AccountNamespaceName)
                    ->WithKeyId(KeyId)
                    ->WithUserId(UserId)
                    ->WithPassword(Password)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            AuthenticationResult = Future->GetTask().Result().ToSharedRef();
            Future->EnsureCompletion();
        }
        {
            const auto Future = AuthClient->LoginBySignature(
                MakeShared<Gs2::Auth::Request::FLoginBySignatureRequest>()
                    ->WithBody(AuthenticationResult->GetBody())
                    ->WithSignature(AuthenticationResult->GetSignature())
                    ->WithKeyId(KeyId)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            if (*Result == nullptr)
            {
                *Result = MakeShared<Gs2::UE5::Auth::Model::FEzAccessToken>();
            }
            (*Result)
                ->WithToken(Future->GetTask().Result()->GetToken())
                ->WithExpire(Future->GetTask().Result()->GetExpire())
                ->WithUserId(Future->GetTask().Result()->GetUserId());
            Future->EnsureCompletion();
        }
        return nullptr;
    }
}
